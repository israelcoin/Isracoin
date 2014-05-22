// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2013-2014 The Dogecoin developers
// Copyright (c)      2014 The Inutoshi developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    //TODO - added hardcoded in_addr_t addresses
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcf;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0x9c;
        vAlertPubKey = ParseHex("04af4780c94216611b0ad88acf18a88a2ed97220a228f22e3af6f02973125d576f874c81d3088988a4fd38820cc807eee415e6abf74d5b5d59c79fcf59e4965830");
        nDefaultPort = 21948;
        nRPCPort = 21947;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 210000;

        const char* pszTimestamp = "Mar-17-2014 Harvard Scientists: First Direct Evidence of Cosmic Inflation";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c6c6a01450f2b8bbb176b98f593623b04a5f5761a7d0adae4d21f77c366e01e147217a9d8864a871d95d182e01d2b003168f0fa7851278a86ac0aa682919f9a6") << OP_CHECKSIG;   //DRG
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1395078549;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 86250;

        hashGenesisBlock = genesis.GetHash();

        //TODO - add genesis block
		assert(hashGenesisBlock == uint256("0x8432ed563657dc92d085fa98b5dfd77975ff50b6bc4be28efe80db615d98a9ae"));
		assert(genesis.hashMerkleRoot == uint256("0xd77b7d90be4dd2cb7161010ac1ffe803b32adacf2111ac190414451ac2308e1d"));

        vSeeds.push_back(CDNSSeedData("israelcoin.org", "dnsseed.israelcoin.org"));

        // Workaround for Boost not being quite compatible with C++11;
        std::vector<unsigned char> pka = list_of(102);
        base58Prefixes[PUBKEY_ADDRESS] = pka;
        
        std::vector<unsigned char> sca = list_of(22);
        base58Prefixes[SCRIPT_ADDRESS] = sca;
        
        // should be 128 more thatn PUBKEY_ADDRESS
        std::vector<unsigned char> sk  = list_of(158);
        base58Prefixes[SECRET_KEY]     = sk;
        
        std::vector<unsigned char> epk = list_of(0x04)(0x88)(0xC4)(0x2E);
        base58Prefixes[EXT_PUBLIC_KEY] = epk;
        
        std::vector<unsigned char> esk = list_of(0x04)(0x88)(0xE1)(0xF4);
        base58Prefixes[EXT_SECRET_KEY] = esk;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const uint64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0xfc;
        vAlertPubKey = ParseHex("04af4780c94216611b0ad88acf18a88a2ed97220a228f22e3af6f02973125d576f874c81d3088988a4fd38820cc807eee415e6abf74d5b5d59c79fcf59e4965830");
        nDefaultPort = 41930;
        nRPCPort = 41929;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        const char* pszTimestamp = "May 13-2014 ynet: Former PM Ehud Olmert jailed for six years for corruption";
        CTransaction txNew;
		txNew.vin.resize(1);
		txNew.vout.resize(1);
		txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		txNew.vout[0].nValue = 1 * COIN;
		txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c6c6a01450f2b8bbb176b98f593623b04a5f5761a7d0adae4d21f77c366e01e147217a9d8864a871d95d182e01d2b003168f0fa7851278a86ac0aa682919f9a6") << OP_CHECKSIG;   //DRG

		CBlock block;
		block.vtx.push_back(txNew);
		block.hashPrevBlock = 0;
		block.hashMerkleRoot = block.BuildMerkleTree();
		block.nVersion = 1;
		block.nTime    = 1399980680;  // DRG
		block.nBits    = 0x1e0ffff0;  //DRG
		block.nNonce   = 548662;  //DRG

		hashGenesisBlock = block.GetHash();
        assert(hashGenesisBlock == uint256("0xbe4a278134704fb27473e89633e34baa886705fcccde5315e40532bd6c867921"));
        genesis = CBlock(block);

        vFixedSeeds.clear();
        vSeeds.clear();
        //TODO
        vSeeds.push_back(CDNSSeedData("israelcoin_testnet.org", "testnet.israelcoin.org"));

        // Workaround for Boost not being quite compatible with C++11;
        std::vector<unsigned char> pka = list_of(113);
		base58Prefixes[PUBKEY_ADDRESS] = pka;

		std::vector<unsigned char> sca = list_of(196);
		base58Prefixes[SCRIPT_ADDRESS] = sca;

		// should be 128 more thatn PUBKEY_ADDRESS
		std::vector<unsigned char> sk  = list_of(241);
		base58Prefixes[SECRET_KEY]     = sk;

		std::vector<unsigned char> epk = list_of(0x04)(0x35)(0xD1)(0xDF);
		base58Prefixes[EXT_PUBLIC_KEY] = epk;

		std::vector<unsigned char> esk = list_of(0x04)(0x35)(0x75)(0xA4);
		base58Prefixes[EXT_SECRET_KEY] = esk;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //TODO
        //assert(hashGenesisBlock == uint256("0x"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
        vSeeds.push_back(CDNSSeedData("",""));
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
