#include "engine_manager.h"

namespace SlimeDB {

EngineManager::status EngineManager::CreateRocksdb(const std::string& rocks_db_path, RocksDBHandle* rdb_handle) {
  ::rocksdb::DBOptions dboptions;
  ::rocksdb::ColumnFamilyOptions cfoptions;
  ::rocksdb::DBWithTTL* pttl_db = NULL;
  std::vector<int32_t> ttls;

  auto status =
      rocksdb::DBWithTTL::Open(dboptions, rocks_db_path, rdb_handle->cfds, &(rdb_handle->cfhs), &pttl_db, ttls);
}
}  // namespace SlimeDB