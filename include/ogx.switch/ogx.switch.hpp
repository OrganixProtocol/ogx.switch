#pragma once

#include <eosio/eosio.hpp>
#include <eosio/name.hpp>
#include <eosio/asset.hpp>
#include <eosio/contract.hpp>
#include <eosio/symbol.hpp>
#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio.system/eosio.system.hpp>
#include <eosio.token/eosio.token.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/permission.hpp>
#include <iterator>
#include <cstring>
#include <vector>
#include <string>

//#define TEST 1
#if TEST
#define EOS_CONTRACT "orgainxtoke1"
#define EOS_CODE "orgainxtoke1"_n
#define EOS symbol{"EOS", 4}
#define TPT_CONTRACT "orgainxtoke2"
#define TPT symbol{"TPT", 4}
#define TPT_CODE "orgainxtoke2"_n
#define OGX_CODE "orgainxtoken"_n
int64_t TPT_OGX_QUOTA = int64_t(5000000) * 10000;
int64_t TPT_THRESHOLD = int64_t(500000) * 10000;
int64_t EOS_THRESHOLD = int64_t(5000) * 10000;
#else
#define EOS_CONTRACT "eosio.token"
#define EOS_CODE "eosio.token"_n
#define EOS symbol{"EOS", 4}
#define TPT_CONTRACT "eosiotptoken"
#define TPT symbol{"TPT", 4}
#define TPT_CODE "eosiotptoken"_n
#define OGX_CODE "organixtoken"_n
int64_t TPT_OGX_QUOTA = int64_t(5000000) * 10000;
int64_t TPT_THRESHOLD = int64_t(500000) * 10000;
int64_t EOS_THRESHOLD = int64_t(5000) * 10000;
#endif

#define FLOAT_SMALL 0.000001

namespace eosiosystem {
    class system_contract;
}

namespace eosio {

    using std::string;

    /**
     * ogx.presale contract defines the structures and actions that allow users to pre sale
     * tokens on EOSIO based blockchains.
     */
    class [[eosio::contract("ogx.presale")]] presale : public contract {
    public:
        using contract::contract;

        presale(eosio::name s, eosio::name code, eosio::datastream<const char *> ds) : contract(s, code, ds),
                                                                                       _pair(s, s.value),
                                                                                       _pair_info(s, s.value) {
        }

        [[eosio::action]]
        void transfer(const name &from,
                      const name &to,
                      const eosio::asset &quantity,
                      const string &memo);

        [[eosio::action]]
        void dist(const name &code, const symbol &symbol, uint64_t num);

        [[eosio::action]]
        void clearpinfo(uint64_t num);

        [[eosio::action]]
        void deletepair(uint64_t id);

        [[eosio::action]]
        void addpair(name code, asset total_balance, asset left_balance, name receive_code, asset receive_balance);

        using transfer_action = eosio::action_wrapper<"transfer"_n, &presale::transfer>;
        using dist_action = eosio::action_wrapper<"dist"_n, &presale::dist>;
    private:
        struct [[eosio::table]] pair {
            uint64_t id;
            name code; //ogx contract
            eosio::asset total_balance; //total sale balance
            eosio::asset left_balance; //left balance
            name receive_code; // contract accepted
            eosio::asset receive_balance; // receive balance

            uint64_t primary_key() const { return id; }

            uint128_t by_token() const { return _ttoi(receive_code, receive_balance.symbol); }

            EOSLIB_SERIALIZE(pair, (id)(code)(total_balance)(left_balance)(receive_code)(receive_balance)
            )
        };

        struct [[eosio::table]] pair_info {
            uint64_t id;
            name receive_code;
            name receive_account;
            eosio::asset receive_balance;
            uint64_t status; // 0: receive, 1: send

            uint64_t primary_key() const { return id; }

            EOSLIB_SERIALIZE(pair_info, (id)(receive_code)(receive_account)(receive_balance)(status)
            )
        };

        typedef eosio::multi_index<"pair"_n, pair, indexed_by < "bytoken"_n,
                const_mem_fun < pair, uint128_t, &pair::by_token> > >
        pair_table;
        typedef eosio::multi_index<"pairinfo"_n, pair_info> pair_info_table;

    private:
        static constexpr eosio::name active_permission{"active"_n};

        static uint128_t _ttoi(eosio::name code, eosio::symbol symbol) {
            return (uint128_t(code.value) << 64) + symbol.raw();
        }

        eosio::presale::pair_table::const_iterator
        _tbytoken_iter(eosio::name code, eosio::symbol symbol) const;

    private:
        pair_info_table _pair_info;
        pair_table _pair;

    };

}

#define EOSIO_DISPATCH_EX(TYPE, MEMBERS) \
            extern "C" { \
                void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
                    auto self = receiver; \
                    if( action == eosio::name("onerror").value) { \
                        /* onerror is only valid if it is for the "eosio" code account and authorized by "eosio"'s "active permission */ \
                        eosio::check(code == eosio::name("eosio").value, "onerror action's are only valid from the \"eosio\" system account"); \
                    } \
                    if((code == self && action != eosio::name("transfer").value) || action == eosio::name("onerror").value || (action == eosio::name("transfer").value && code != self)) { \
                            switch( action ) { \
                            EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
                        } \
                    } \
                } \
            } \

EOSIO_DISPATCH_EX(eosio::presale, (transfer)(dist)(deletepair)(addpair)(clearpinfo))
