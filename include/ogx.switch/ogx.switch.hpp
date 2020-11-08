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

#define TEST 1
#if TEST
#define OGX_CODE "orgainxtoken"_n
#define NEW_OGX_CODE "orgainxtoken"_n
#else
#define OGX_CODE "organixtoken"_n
#define NEW_OGX_CODE "organixtoken"_n
#endif

namespace eosiosystem {
    class system_contract;
}

namespace eosio {

    using std::string;

    /**
     * ogx.switch contract defines the structures and actions that allow users to pre sale
     * tokens on EOSIO based blockchains.
     */
    class [[eosio::contract("ogx.switch")]] ogxswitch : public contract {
    public:
        using contract::contract;

        ogxswitch(eosio::name s, eosio::name code, eosio::datastream<const char *> ds) : contract(s, code, ds) {
        }

        void transfer(const name &from,
                      const name &to,
                      const eosio::asset &quantity,
                      const string &memo);

    private:
        static constexpr eosio::name active_permission{"active"_n};

        static uint128_t _ttoi(eosio::name code, eosio::symbol symbol) {
            return (uint128_t(code.value) << 64) + symbol.raw();
        }
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

EOSIO_DISPATCH_EX(eosio::ogxswitch, (transfer))
