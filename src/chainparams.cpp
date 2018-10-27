// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcf;
        pchMessageStart[1] = 0x2a;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0x8e;
        vAlertPubKey = ParseHex("04e317aba52be44f4cb4fb5a030fa014328cc85415dcdd1172cfaca76af8dd39f58c99b2ff743fd742cdaa2641d6817aa861e60bf751c029c2703f08dc726f1cd2");
        nDefaultPort = 7214;
        nRPCPort = 7215;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block.
            // transaction:  Coinbase(hash=3c8eb5ab2277426f2f48bd70eeb32416b1c94456a3e56e1871d15b568dde3e1e, nTime=1518409800, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            // CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a284f63742032322c20323031373a20426974636f696e2070726963652061626f76652024362c303030)
            // CTxOut(empty)

        const char* pszTimestamp = "Start PayDay Coin at Saturday, 13-Oct-18 00:00:00 UTC (Test)";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1539388800, vin, vout, 0);

        //LogPrintf("Genesis mainnet Transaction:  %s\n", txNew.ToString().c_str());

        genesis.vtx.push_back(txNew);

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1539388800;
        genesis.nBits = 504365040; // bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 10285;

        hashGenesisBlock = genesis.GetHash();
        if (hashGenesisBlock != uint256("0x02a5367b5a7755c16c79ca39fe34ab336347998ede8cd4552cfe1b00b95a276e") ) {
            LogPrintf("================Genesis error===================\n");
            LogPrintf("Genesis hash: %s \n", genesis.GetHash().ToString().c_str());
            LogPrintf("Genesis nTime: %s \n", genesis.nTime);
            LogPrintf("Genesis nBits: %s \n", genesis.nBits);
            LogPrintf("Genesis nNonce: %s \n", genesis.nNonce);
            LogPrintf("Genesis Merkle: %s \n", genesis.hashMerkleRoot.ToString().c_str());
            LogPrintf("===================================\n");
        }
        assert(hashGenesisBlock == uint256("0x02a5367b5a7755c16c79ca39fe34ab336347998ede8cd4552cfe1b00b95a276e"));
        assert(genesis.hashMerkleRoot == uint256("0x6aa0342003fef32d0416d3cb3853bf056c8ed42dcd1e6d8bab28af1452ba60a3"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,83);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();


/*
		vSeeds.push_back(CDNSSeedData("a",  "19.18.17.10"));
		vSeeds.push_back(CDNSSeedData("b",  "19.18.17.11"));
		vSeeds.push_back(CDNSSeedData("c",  "19.18.17.12"));
		vSeeds.push_back(CDNSSeedData("d",  "19.18.17.20"));
		vSeeds.push_back(CDNSSeedData("e",  "19.18.17.21"));
*/
/*

        vSeeds.push_back(CDNSSeedData("a.paydaycoin.io",  "a.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("b.paydaycoin.io",  "b.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("c.paydaycoin.io",  "c.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("d.paydaycoin.io",  "d.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("e.paydaycoin.io",  "e.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("f.paydaycoin.io",  "f.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("g.paydaycoin.io",  "g.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("h.paydaycoin.io",  "h.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("i.paydaycoin.io",  "i.paydaycoin.io"));
        vSeeds.push_back(CDNSSeedData("j.paydaycoin.io",  "j.paydaycoin.io"));
*/
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
        //vFixedSeeds.clear();
        //vSeeds.clear();

        //getHardcodedSeeds(vFixedSeeds);

        /*
        "PrivateKey" : "3081d3020101042088a47d39f79604260a09134e1515f1d3949fb867c13c4a94ab8c0b96c5e7f747a08185308182020101302c06072a8648ce3d0101022100fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f300604010004010704210279be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798022100fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141020101a124032200033c5cb4f6383ff3f53d53d13c9fd37747cc885b3006e612219f89472c0a28bdc1"
        "PublicKey" : "043c5cb4f6383ff3f53d53d13c9fd37747cc885b3006e612219f89472c0a28bdc1865ba788e8e832878cae5eedb4831011d5295e47f1cea6d13a43edd37af41417"
        */
        nPoolMaxTransactions = 3;
        //strSporkKey = "043c5cb4f6383ff3f53d53d13c9fd37747cc885b3006e612219f89472c0a28bdc1865ba788e8e832878cae5eedb4831011d5295e47f1cea6d13a43edd37af41417";
        //strMasternodePaymentsPubKey = "043c5cb4f6383ff3f53d53d13c9fd37747cc885b3006e612219f89472c0a28bdc1865ba788e8e832878cae5eedb4831011d5295e47f1cea6d13a43edd37af41417";
        strDarksendPoolDummyAddress = "MWc1TrChdsnY7bPJbQDeyhkyeC8YHmzrx1";

        nLastPOWBlock = 100000;
        nPOSStartBlock = 100;
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
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0x3d;
        pchMessageStart[3] = 0xe8;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04e317aba52be44f4cb4fb5a030fa014328cc85415dcdd1172cfaca76af8dd39f58c99b2ff743fd742cdaa2641d6817aa861e60bf751c029c2703f08dc726f1cd2");
        nDefaultPort = 7214;
        nRPCPort = 7215;
        strDataDir = "testnet";

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x02a5367b5a7755c16c79ca39fe34ab336347998ede8cd4552cfe1b00b95a276e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,73);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,83);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


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
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
