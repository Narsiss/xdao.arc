#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>
#include <eosio/time.hpp>

#include "mdao.conf.db.hpp"

using namespace eosio;
using namespace mdao;

class [[eosio::contract("mdaoconftes1")]] mdaoconf : public contract {
private:
    conf_global_t            _gstate;
    conf_global_singleton    _global;

public:
    using contract::contract;

    mdaoconf(name receiver, name code, datastream<const char*> ds):
        contract(receiver, code, ds), _global(_self, _self.value) {
        if (_global.exists()) {
            _gstate = _global.get();

        } else {
            _gstate = conf_global_t{};
        }
    }

    ~mdaoconf() {
        _global.set( _gstate, get_self() );
        // _global.remove();

    }

    ACTION migrate() {
        _gstate.status          = conf_status::RUNNING;
    }

    ACTION init( const name& fee_taker, const app_info& app_info, const asset& dao_upg_fee, const name& admin, const name& status );
    ACTION setseat( uint16_t& dappmax );
    ACTION setmanager( const name& manage_type, const name& manager );
    ACTION setsystem( const name& token_contract, const name& ntoken_contract, uint16_t stake_delay_days );
    ACTION setmetaverse( const bool& enable_metaverse );
    ACTION settokenfee( const asset& quantity );

};