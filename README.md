# Introduction
- 这是一个支持弹性扩缩容，行列混存，基于rocksdb engine的kv分布式存储数据库！

# TODO
- 目前正在做KV node服务，这是SlimeDB的存储层。一个node下会有多个不同region的副本，通过grpc来相互通信，借助meta服务实现同步
    - engine manager：提供基于rocksdb的存储接口，如CURD，副本复制，副本ingest等
    - region manager：管理每个region相关的信息，例如region hash范围，元信息
    - node manager：负责处理各种rpc，并负责各个模块线程的调度
    - 线程模型：各个模块的线程，以及映射到cpu core的模型