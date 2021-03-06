// BSD 3-Clause License; see https://github.com/jpivarski/awkward-1.0/blob/master/LICENSE

#ifndef AWKWARD_INDEXEDBUILDER_H_
#define AWKWARD_INDEXEDBUILDER_H_

#include <vector>

#include "awkward/cpu-kernels/util.h"
#include "awkward/array/IndexedArray.h"
#include "awkward/builder/ArrayBuilderOptions.h"
#include "awkward/builder/GrowableBuffer.h"
#include "awkward/builder/Builder.h"

namespace awkward {
  template <typename T>
  class EXPORT_SYMBOL IndexedBuilder: public Builder {
  public:
    IndexedBuilder(const ArrayBuilderOptions& options,
                   const GrowableBuffer<int64_t>& index,
                   const std::shared_ptr<T>& array,
                   bool hasnull);

    const Content*
      arrayptr() const;

    int64_t
      length() const override;

    void
      clear() override;

    bool
      active() const override;

    const BuilderPtr
      null() override;

    const BuilderPtr
      boolean(bool x) override;

    const BuilderPtr
      integer(int64_t x) override;

    const BuilderPtr
      real(double x) override;

    const BuilderPtr
      string(const char* x, int64_t length, const char* encoding) override;

    const BuilderPtr
      beginlist() override;

    const BuilderPtr
      endlist() override;

    const BuilderPtr
      begintuple(int64_t numfields) override;

    const BuilderPtr
      index(int64_t index) override;

    const BuilderPtr
      endtuple() override;

    const BuilderPtr
      beginrecord(const char* name, bool check) override;

    const BuilderPtr
      field(const char* key, bool check) override;

    const BuilderPtr
      endrecord() override;

  protected:
    const ArrayBuilderOptions options_;
    GrowableBuffer<int64_t> index_;
    const std::shared_ptr<T> array_;
    bool hasnull_;
  };

  class IndexedGenericBuilder: public IndexedBuilder<Content> {
  public:
    static const BuilderPtr
    fromnulls(const ArrayBuilderOptions& options,
              int64_t nullcount,
              const ContentPtr& array);

    IndexedGenericBuilder(const ArrayBuilderOptions& options,
                          const GrowableBuffer<int64_t>& index,
                          const ContentPtr& array,
                          bool hasnull);

    const std::string
      classname() const override;

    const ContentPtr
      snapshot() const override;

    const BuilderPtr
      append(const ContentPtr& array, int64_t at) override;
  };

  class IndexedI32Builder: public IndexedBuilder<IndexedArray32> {
  public:
    IndexedI32Builder(const ArrayBuilderOptions& options,
                      const GrowableBuffer<int64_t>& index,
                      const std::shared_ptr<IndexedArray32>& array,
                      bool hasnull);

    const std::string
      classname() const override;

    const ContentPtr
      snapshot() const override;

    const BuilderPtr
      append(const ContentPtr& array, int64_t at) override;
  };

  class IndexedIU32Builder: public IndexedBuilder<IndexedArrayU32> {
  public:
    IndexedIU32Builder(const ArrayBuilderOptions& options,
                       const GrowableBuffer<int64_t>& index,
                       const std::shared_ptr<IndexedArrayU32>& array,
                       bool hasnull);

    const std::string
      classname() const override;

    const ContentPtr
      snapshot() const override;

    const BuilderPtr
      append(const ContentPtr& array, int64_t at) override;
  };

  class IndexedI64Builder: public IndexedBuilder<IndexedArray64> {
  public:
    IndexedI64Builder(const ArrayBuilderOptions& options,
                      const GrowableBuffer<int64_t>& index,
                      const std::shared_ptr<IndexedArray64>& array,
                      bool hasnull);

    const std::string
      classname() const override;

    const ContentPtr
      snapshot() const override;

    const BuilderPtr
      append(const ContentPtr& array, int64_t at) override;
  };

  class IndexedIO32Builder: public IndexedBuilder<IndexedOptionArray32> {
  public:
    IndexedIO32Builder(const ArrayBuilderOptions& options,
                       const GrowableBuffer<int64_t>& index,
                       const std::shared_ptr<IndexedOptionArray32>& array,
                       bool hasnull);

    const std::string
      classname() const override;

    const ContentPtr
      snapshot() const override;

    const BuilderPtr
      append(const ContentPtr& array, int64_t at) override;
  };

  class IndexedIO64Builder: public IndexedBuilder<IndexedOptionArray64> {
  public:
    IndexedIO64Builder(const ArrayBuilderOptions& options,
                       const GrowableBuffer<int64_t>& index,
                       const std::shared_ptr<IndexedOptionArray64>& array,
                       bool hasnull);

    const std::string
      classname() const override;

    const ContentPtr
      snapshot() const override;

    const BuilderPtr
      append(const ContentPtr& array, int64_t at) override;
  };

}

#endif // AWKWARD_INDEXEDBUILDER_H_
