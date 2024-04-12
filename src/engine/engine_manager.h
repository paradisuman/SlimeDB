#include <string>
#include <map>

#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include <rocksdb/utilities/db_ttl.h>
#include <optional>

namespace SlimeDB {

struct RocksDBHandle {
  rocksdb::DB* db;
  std::vector<rocksdb::ColumnFamilyHandle*> cfhs;
  std::vector<rocksdb::ColumnFamilyHandle*> meta_cfhs;
  std::vector<rocksdb::ColumnFamilyDescriptor> cfds;
  SlimeDB::SlimeEnv env;
  std::shared_ptr<rocksdb::SstFileManager> db_sst_file_manager;
  std::shared_ptr<rocksdb::Statistics> db_statistics;

  ~RocksDBHandle() {
    if (db) {
      for (auto* cfh : cfhs) {
        if (cfh) {
          db->DestroyColumnFamilyHandle(cfh);
        }
      }

      for (auto* meta_cfh : meta_cfhs) {
        if (meta_cfh) {
          db->DestroyColumnFamilyHandle(meta_cfh);
        }
      }

      delete db;
      db = nullptr;
    }
  }
};

class EngineManager {
  using status = ::rocksdb::Status;

 public:
  // 支持ttl
  // 支持ingest数据
  // 支持创建一份数据副本
  void GetKV(const std::string& key, const uint32_t cf_id, std::string& value);
  void PutKV(const std::string& key, const std::string& value, const uint32_t cf_id);
  void DelKV(const std::string& key, uint32_t cf_id);
  status CreateRocksdb(const std::string& rocks_db_path, RocksDBHandle* rdb_handle);
  void Open();
  void FullCompaction();
  void concurrent_flush_memtable();
  void Flush();
  // 直接写 or sst后写
  void Ingest();
  // 从快照直接dump一份
  void CreateIngestion();
  status CreateCheckpoint();

  ~EngineManager() {}

 private:
  std::string rocksdb_name_;
  rocksdb::DB* db;
  rocksdb::Options options;
};
}  // namespace SlimeDB