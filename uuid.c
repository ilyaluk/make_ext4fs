/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>

#include <arpa/inet.h>

#include "ext4_utils.h"
#include "sha1.h"
#include "uuid.h"

/* Definition from RFC-4122 */
struct uuid {
	u32 time_low;
	u16 time_mid;
	u16 time_hi_and_version;
	u8 clk_seq_hi_res;
	u8 clk_seq_low;
	u16 node0_1;
	u32 node2_5;
};

static void sha1_hash(const char *namespace, const char *name,
	unsigned char sha1[SHA1_DIGEST_LENGTH])
{
	SHA1_CTX ctx;
	SHA1Init(&ctx);
	SHA1Update(&ctx, (const u8*)namespace, strlen(namespace));
	SHA1Update(&ctx, (const u8*)name, strlen(name));
	SHA1Final(sha1, &ctx);
}

void generate_uuid(const char *namespace, const char *name, u8 result[16])
{
	unsigned char sha1[SHA1_DIGEST_LENGTH];
	struct uuid *uuid = (struct uuid *)result;

	sha1_hash(namespace, name, (unsigned char*)sha1);
	memcpy(uuid, sha1, sizeof(struct uuid));

	uuid->time_low = ntohl(uuid->time_low);
	uuid->time_mid = ntohs(uuid->time_mid);
	uuid->time_hi_and_version = ntohs(uuid->time_hi_and_version);
	uuid->time_hi_and_version &= 0x0FFF;
	uuid->time_hi_and_version |= (5 << 12);
	uuid->clk_seq_hi_res &= ~(1 << 6);
	uuid->clk_seq_hi_res |= 1 << 7;
}

void uuid_parse(const char *uuid_str, u8 result[16])
{
    int i, j;
    for (i = 0, j = 0; i < 36; i++) {
        if (uuid_str[i] == '-') continue;
        if (j < 16) {
            sscanf(&uuid_str[i], "%2hhx", &result[j]);
            i++;
            j++;
        }
    }
}

void uuid_to_str(const u8 uuid[16], char uuid_str[37])
{
    sprintf(uuid_str, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-"
            "%02x%02x%02x%02x%02x%02x",
            uuid[0], uuid[1], uuid[2], uuid[3],
            uuid[4], uuid[5], uuid[6], uuid[7],
            uuid[8], uuid[9], uuid[10], uuid[11],
            uuid[12], uuid[13], uuid[14], uuid[15]);
}
