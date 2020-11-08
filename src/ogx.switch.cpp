#include <ogx.switch/ogx.switch.hpp>

namespace eosio {

    presale::pair_table::const_iterator
    presale::_tbytoken_iter(eosio::name code, eosio::symbol symbol) const {
        auto idx = _pair.get_index<"bytoken"_n>();
        auto it = idx.lower_bound(_ttoi(code, symbol));
        if (it != idx.end()) {
            if (it->receive_code == code && it->receive_balance.symbol == symbol) {
                return _pair.find(it->id);
            }
        }
        return _pair.end();
    }

    void presale::dist(const eosio::name &code, const eosio::symbol &symbol, uint64_t num) {
        require_auth(get_self());

        auto it = _tbytoken_iter(code, symbol);
        check(it != _pair.end(), code.to_string() + " " + symbol.code().to_string() + " token not exists");

        auto rate = 0.0;
        auto needed_balance = asset{int64_t(TPT_OGX_QUOTA / 0.03958), symbol};
        //超过的情况
        if (it->receive_balance > needed_balance) {
            rate = (FLOAT_SMALL + it->receive_balance.amount - needed_balance.amount) / it->receive_balance.amount;
        }
        for (auto it1 = _pair_info.cbegin(); it1 != _pair_info.cend() && num > 0; ++it1) {
            if (!(it1->receive_code == TPT_CODE && it1->receive_balance.symbol == symbol)) {
                continue;
            }
            if (it1->status != 0) {
                continue;
            }
            //计算占比
            auto balance = asset{
                    int64_t((it1->receive_balance.amount + FLOAT_SMALL) / it->receive_balance.amount *
                            it->total_balance.amount),
                    it->total_balance.symbol};
            if (balance.amount > 0) {
                action(
                        permission_level{OGX_CODE, active_permission},// 权限
                        OGX_CODE, // 合约
                        name("transfer"), // 行为
                        std::make_tuple(OGX_CODE, it1->receive_account, balance, std::string("swap success")) // 参数
                ).send();
            } else {
                check(false, it1->receive_account.to_string() + " " + balance.to_string());
            }
            _pair.modify(it, get_self(), [&](auto &s) {
                s.left_balance -= balance;
            });
            //是否需要退回
            if (rate > 0) {
                auto balance = asset{int64_t(rate * it1->receive_balance.amount), symbol};
                if (balance.amount > 0) {
                    action(
                            permission_level{get_self(), active_permission},// 权限
                            it1->receive_code, // 合约
                            name("transfer"), // 行为
                            std::make_tuple(get_self(), it1->receive_account, balance, std::string("back")) // 参数
                    ).send();
                } else {
                    check(false, balance.to_string());
                }
            }
            _pair_info.modify(it1, get_self(), [&](auto &s) {
                s.status = 1;
            });
            num--;
        }
    }

    void presale::transfer(const name &from,
                           const name &to,
                           const asset &quantity,
                           const string &memo) {
        require_auth(from);
        if (!(from != get_self() && to == get_self()) || from == "eosio.stake"_n) {
            return;
        }
#if TEST
        auto timestamp = current_time_point().time_since_epoch().to_seconds();
        check(timestamp >= 1597479600 && timestamp <= 1597480200,
              "not beginning or having ended");
#else
/*        auto timestamp = current_time_point().time_since_epoch().to_seconds();
        check(timestamp >= 1597492800 && timestamp <= 1597500000,
              "not beginning or having ended");*/
#endif
        check(memo.size() <= 256, "memo has more than 256 bytes");

        if (get_first_receiver() == TPT_CODE) {
            auto min_threshold = asset{int64_t(TPT_THRESHOLD), quantity.symbol};
            check(quantity.is_valid() && quantity >= min_threshold,
                  "lower than TPT minimum threshold " + min_threshold.to_string());
        } else if (get_first_receiver() == EOS_CODE) {
            auto max_threshold = asset{int64_t(EOS_THRESHOLD), quantity.symbol};
            check(quantity.is_valid() && quantity.amount > 0 &&
                  quantity <= max_threshold,
                  "lager than EOS maximum threshold " + max_threshold.to_string());
        }
        auto it = _tbytoken_iter(get_first_receiver(), quantity.symbol);
        check(it != _pair.end(),
              get_first_receiver().to_string() + " " + quantity.symbol.code().to_string() + " token not exists");

        if (get_first_receiver() == EOS_CODE) {
            auto swap_asset = asset{int64_t(quantity.amount * 70.6697), it->total_balance.symbol};
            if (it->left_balance < swap_asset) {
                auto back_balance = asset{int64_t((swap_asset.amount - it->left_balance.amount) / 70.6697),
                                          quantity.symbol};
                action(
                        permission_level{get_self(), active_permission},// 权限
                        it->receive_code, // 合约
                        name("transfer"), // 行为
                        std::make_tuple(get_self(), from, back_balance, std::string("")) // 参数
                ).send();
                swap_asset = it->left_balance;
            }
            _pair.modify(it, get_self(), [&](auto &s) {
                s.left_balance -= swap_asset;
                s.receive_balance += quantity;
            });
            action(
                    permission_level{OGX_CODE, active_permission},// 权限
                    OGX_CODE, // 合约
                    name("transfer"), // 行为
                    std::make_tuple(OGX_CODE, from, swap_asset, std::string("swap success")) // 参数
            ).send();
        } else if (get_first_receiver() == TPT_CODE) {
            _pair.modify(it, get_self(), [&](auto &s) {
                s.receive_balance += quantity;
            });

            _pair_info.emplace(get_self(), [&](auto &s) {
                s.id = _pair_info.available_primary_key();
                s.receive_code = get_first_receiver();
                s.receive_account = from;
                s.receive_balance = quantity;
                s.status = 0;
            });
        }
    }

    void
    presale::addpair(name code, asset total_balance, asset left_balance, name receive_code, asset receive_balance) {
        require_auth(get_self());

        _pair.emplace(_self, [&](auto &s) {
            s.id = _pair.available_primary_key();
            s.code = code;
            s.total_balance = total_balance;
            s.left_balance = left_balance;
            s.receive_code = receive_code;
            s.receive_balance = receive_balance;
        });
    }

    void presale::deletepair(uint64_t id) {
        require_auth(get_self());

        auto it = _pair.find(id);
        check(it != _pair.end(), "id doesn't exist");
        _pair.erase(it);
    }

    void presale::clearpinfo(uint64_t num) {
        require_auth(get_self());

        auto it1 = _pair_info.cbegin();
        while (it1 != _pair_info.cend() && num > 0) {
            _pair_info.erase(it1);

            num--;
            it1 = _pair_info.cbegin();
        }
    }


} /// namespace eosio
