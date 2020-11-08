#include <ogx.switch/ogx.switch.hpp>

namespace eosio {

    void ogxswitch::transfer(const name &from,
                             const name &to,
                             const asset &quantity,
                             const string &memo) {
        require_auth(from);
        if (!(from != get_self() && to == get_self())) {
            return;
        }
        check(memo.size() <= 256, "memo has more than 256 bytes");

        check(get_first_receiver() == OGX_CODE, "contract invalid");

        auto back_balance = asset{int64_t(quantity * 10000), quantity.symbol};
        action(
                permission_level{get_self(), active_permission},// 权限
                NEW_OGX_CODE, // 合约
                name("transfer"), // 行为
                std::make_tuple(get_self(), from, back_balance, std::string("switch")) // 参数
        ).send();

    }

} /// namespace eosio
