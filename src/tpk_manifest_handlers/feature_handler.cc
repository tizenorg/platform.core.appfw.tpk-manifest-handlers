// Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
// Use of this source code is governed by an apache-2.0 license that can be
// found in the LICENSE file.

#include "tpk_manifest_handlers/feature_handler.h"

namespace {

const char kFeatureKey[] = "manifest.feature";
const char kFeatureName[] = "@name";
const char kFeatureText[] = "#text";
const char kFeatureRequirementText[] = "true";

}  // namespace

namespace tpk {
namespace parse {

std::string FeatureInfo::Key() {
  return kFeatureKey;
}

bool FeatureHandler::Parse(
    const parser::Manifest& manifest,
    std::shared_ptr<parser::ManifestData>* output,
    std::string* /*error*/) {
  auto data = std::make_shared<FeatureInfo>();
  for (auto& feature_dict :
      parser::GetOneOrMany(manifest.value(), kFeatureKey, "")) {
    std::string name;
    if (feature_dict->GetString(kFeatureName, &name)) {
      std::string text;
      feature_dict->GetString(kFeatureText, &text);
      if (text.empty() || text == kFeatureRequirementText)
        data->Add(name);
    }
  }
  *output = std::static_pointer_cast<parser::ManifestData>(data);
  return true;
}

std::string FeatureHandler::Key() const {
  return FeatureInfo::Key();
}

}  // namespace parse
}  // namespace tpk
