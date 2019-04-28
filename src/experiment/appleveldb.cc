#include <unistd.h>
#include <iostream>
#include <cassert>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

int main()
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status statsu = leveldb::DB::Open(options, "/tmp/testdb", &db);
    assert(statsu.ok());

    std::string value = "hello world";
    std::string key1 = "key1", key2 = "key1";
    {
        // prepare
        leveldb::Status s = db->Put(leveldb::WriteOptions(), key1, value);
        // read & write
        s = db->Get(leveldb::ReadOptions(), key1, &value);
        if (s.ok())
        {
            s = db->Put(leveldb::WriteOptions(), key2, value);
        }
        if (s.ok())
        {
            s = db->Delete(leveldb::WriteOptions(), key1);
        }

        std::cout << "first time: \n";
        leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next())
        {
            std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
        }
        assert(it->status().ok());
        delete it;
    }

    {
        std::cout << "with snapshot: \n"; // sanme output with above output
        // generate snapshot
        leveldb::ReadOptions options;
        options.snapshot = db->GetSnapshot();

        leveldb::Status s = db->Put(leveldb::WriteOptions(), "sprint", "rain");
        leveldb::Iterator *it = db->NewIterator(options);
        for (it->SeekToFirst(); it->Valid(); it->Next())
        {
            std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
        }
        delete it;
        db->ReleaseSnapshot(options.snapshot);
    }

    {
        // prepare
        leveldb::Status s = db->Put(leveldb::WriteOptions(), key1, value);
        // atomic updates
        s = db->Get(leveldb::ReadOptions(), key1, &value);
        if (s.ok())
        {
            leveldb::WriteBatch batch;
            batch.Delete(key1);
            batch.Put(key2, value);
            s = db->Write(leveldb::WriteOptions(), &batch);
        }

        std::cout << "second time: \n";
        leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next())
        {
            std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
        }
        assert(it->status().ok());
        delete it;
    }

    delete db;
}