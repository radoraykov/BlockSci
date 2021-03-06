//
//  hash.cpp
//  blocksci_devel
//
//  Created by Harry Kalodner on 3/10/17.
//  Copyright © 2017 Harry Kalodner. All rights reserved.
//

#include "hash.hpp"

#include <openssl/sha.h>
#include <openssl/ripemd.h>


blocksci::uint256 sha256(const uint8_t *data, size_t len) {
    blocksci::uint256 hash;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, len);
    SHA256_Final((unsigned char *)&hash, &sha256);
    return hash;
}

blocksci::uint256 sha256(const unsigned char *begin, const unsigned char *end) {
    return sha256(static_cast<const uint8_t *>(begin), end - begin);
}

bool base58_sha256(void *digest, const void *data, size_t datasz) {
    auto hash = sha256(reinterpret_cast<const uint8_t *>(data), datasz);
    memcpy(digest, &hash, sizeof(hash));
    return true;
}

blocksci::uint256 doubleSha256(const char *data, unsigned long len) {
    blocksci::uint256 txHash = sha256((const uint8_t *)data, len);
    txHash = sha256((const uint8_t *)&txHash, sizeof(blocksci::uint256));
    return txHash;
}

blocksci::uint160 ripemd160(const char *data, unsigned long len) {
    blocksci::uint160 hash;
    RIPEMD160_CTX ripemd;
    RIPEMD160_Init(&ripemd);
    RIPEMD160_Update(&ripemd, data, len);
    RIPEMD160_Final((unsigned char *)&hash, &ripemd);
    return hash;
}

blocksci::uint160 hash160(const void *data, unsigned long len) {
    auto hashed = sha256(reinterpret_cast<const uint8_t *>(data), len);
    return ripemd160(reinterpret_cast<const char *>(&hashed), sizeof(hashed));
}
