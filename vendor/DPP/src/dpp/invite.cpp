/************************************************************************************invi
 *
 * D++, A Lightweight C++ library for Discord
 *
 * Copyright 2021 Craig Edwards and D++ contributors 
 * (https://github.com/brainboxdotcc/DPP/graphs/contributors)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/
#include <dpp/invite.h>
#include <dpp/discordevents.h>
#include <dpp/json.h>



namespace dpp {

using json = nlohmann::json;

invite::invite() : expires_at(0), guild_id(0), channel_id(0), inviter_id(0), target_user_id(0), target_type(0), approximate_presence_count(0), approximate_member_count(0), max_age(86400), max_uses(0), temporary(false), unique(false), uses(0), created_at(0)
{
}

invite& invite::fill_from_json(nlohmann::json* j) {
	code = string_not_null(j, "code");
	expires_at = (j->contains("expires_at")) ? ts_not_null(j, "expires_at") : 0;
	created_at = (j->contains("created_at")) ? ts_not_null(j, "created_at") : 0;
	if (j->contains("guild") && !j->at("guild").is_null()) {
		guild_id = snowflake_not_null(&((*j)["guild"]), "id");
	} else if (j->contains("guild_id")) { // check ID for the invite create event
		guild_id = snowflake_not_null(j, "guild_id");
	}
	if (j->contains("channel") && !j->at("channel").is_null()) {
		channel_id = snowflake_not_null(&((*j)["channel"]), "id");
	} else if (j->contains("channel_id")) { // check ID for the invite create event
		channel_id = snowflake_not_null(j, "channel_id");
	}
	inviter_id = (j->contains("inviter")) ? snowflake_not_null(&((*j)["inviter"]), "id") : 0;
	target_user_id = (j->contains("target_user")) ? snowflake_not_null(&((*j)["target_user"]), "id") : 0;
	target_type = int8_not_null(j, "target_type");
	approximate_presence_count = int32_not_null(j, "approximate_presence_count");
	approximate_member_count = int32_not_null(j, "approximate_member_count");
	max_age = int32_not_null(j, "max_age");
	max_uses = int32_not_null(j, "max_uses");
	temporary = bool_not_null(j, "temporary");
	unique = bool_not_null(j, "unique");
	uses = (j->contains("uses")) ? int32_not_null(j, "uses") : 0;
	if (j->contains("stage_instance")) {
		stage = stage_instance().fill_from_json(&((*j)["stage_instance"]));
	}
	return *this;
}

std::string invite::build_json(bool with_id) const {
	json j;
	j["max_age"] = max_age;
	j["max_uses"] = max_uses;
	if (target_user_id > 0)
		j["target_user"] = target_user_id;
	if (target_type > 0)
		j["target_type"] = target_type;
	if (temporary)
		j["temporary"] = temporary;
	if (unique)
		j["unique"] = unique;
	return j.dump();
}

};
