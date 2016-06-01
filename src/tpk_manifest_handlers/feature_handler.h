// Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
// Use of this source code is governed by an apache-2.0 license that can be
// found in the LICENSE file.

#ifndef TPK_MANIFEST_HANDLERS_FEATURE_HANDLER_H_
#define TPK_MANIFEST_HANDLERS_FEATURE_HANDLER_H_

#include <string>
#include <vector>

#include "manifest_parser/manifest_handler.h"

namespace tpk {
namespace parse {

class FeatureInfo : public parser::ManifestData {
 public:
  static std::string Key();

  const std::vector<std::string>& features() const {
    return features_;
  }

  void Add(const std::string& feature) {
    features_.push_back(feature);
  }

 private:
  std::vector<std::string> features_;
};

/**
 * @brief The AccountHandler class
 *
 * Handler of tizen-manifest.xml for xml elements:
 *  <feature>
 */
class FeatureHandler : public parser::ManifestHandler {
 public:
  bool Parse(
      const parser::Manifest& manifest,
      std::shared_ptr<parser::ManifestData>* output,
      std::string* error) override;
  std::string Key() const override;
};

}  // namespace parse
}  // namespace tpk

#endif  // TPK_MANIFEST_HANDLERS_FEATURE_HANDLER_H_
