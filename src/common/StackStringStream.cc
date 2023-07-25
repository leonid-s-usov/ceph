#include "common/StackStringStream.h"

CachedStackStringStream::CachedStackStringStream()
{
  if (cache.destructed || cache.c.empty()) {
    osp = std::make_unique<sss>();
  } else {
    osp = std::move(cache.c.back());
    cache.c.pop_back();
    osp->reset();
  }
}

CachedStackStringStream::~CachedStackStringStream()
{
  if (!cache.destructed && cache.c.size() < max_elems) {
    cache.c.emplace_back(std::move(osp));
  }
}

CachedStackStringStream::Cache::Cache()
{

}
    
CachedStackStringStream::Cache::~Cache() {
  destructed = true;
}
