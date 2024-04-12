#include <map>
#include <string>

namespace SlimeDB {

class StoreManager {
 public:
 private:
  // std::unordered_map<std::string, uint32_t> region_map_;
  std::unordered_map<uint32_t, slime_region> region_map_;
  EngineManager db_manager_;
};

}  // namespace SlimeDB
