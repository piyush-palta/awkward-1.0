// BSD 3-Clause License; see https://github.com/jpivarski/awkward-1.0/blob/master/LICENSE

#ifndef AWKWARD_LISTOFFSETARRAY_H_
#define AWKWARD_LISTOFFSETARRAY_H_

#include <memory>

#include "awkward/cpu-kernels/util.h"
#include "awkward/Index.h"
#include "awkward/Identities.h"
#include "awkward/Content.h"

namespace awkward {
  template <typename T>
  class EXPORT_SYMBOL ListOffsetArrayOf: public Content {
  public:
    ListOffsetArrayOf<T>(const IdentitiesPtr& identities,
                         const util::Parameters& parameters,
                         const IndexOf<T>& offsets,
                         const ContentPtr& content);

    const IndexOf<T>
      starts() const;

    const IndexOf<T>
      stops() const;

    const IndexOf<T>
      offsets() const;

    const ContentPtr
      content() const;

    Index64
      compact_offsets64(bool start_at_zero) const;

    const ContentPtr
      broadcast_tooffsets64(const Index64& offsets) const;

    const ContentPtr
      toRegularArray() const;

    const ContentPtr
      toListOffsetArray64(bool start_at_zero) const;

    const std::string
      classname() const override;

    void
      setidentities() override;

    void
      setidentities(const IdentitiesPtr& identities) override;

    const TypePtr
      type(const util::TypeStrs& typestrs) const override;

    const std::string
      tostring_part(const std::string& indent,
                    const std::string& pre,
                    const std::string& post) const override;

    void
      tojson_part(ToJson& builder) const override;

    void
      nbytes_part(std::map<size_t, int64_t>& largest) const override;

    int64_t
      length() const override;

    const ContentPtr
      shallow_copy() const override;

    const ContentPtr
      deep_copy(bool copyarrays,
                bool copyindexes,
                bool copyidentities) const override;

    void
      check_for_iteration() const override;

    const ContentPtr
      getitem_nothing() const override;

    const ContentPtr
      getitem_at(int64_t at) const override;

    const ContentPtr
      getitem_at_nowrap(int64_t at) const override;

    const ContentPtr
      getitem_range(int64_t start, int64_t stop) const override;

    const ContentPtr
      getitem_range_nowrap(int64_t start, int64_t stop) const override;

    const ContentPtr
      getitem_field(const std::string& key) const override;

    const ContentPtr
      getitem_fields(const std::vector<std::string>& keys) const override;

    const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceItemPtr& slicecontent,
                          const Slice& tail) const override;

    const ContentPtr
      carry(const Index64& carry) const override;

    const std::string
      purelist_parameter(const std::string& key) const override;

    bool
      purelist_isregular() const override;

    int64_t
      purelist_depth() const override;

    const std::pair<int64_t, int64_t>
      minmax_depth() const override;

    const std::pair<bool, int64_t>
      branch_depth() const override;

    int64_t
      numfields() const override;

    int64_t
      fieldindex(const std::string& key) const override;

    const std::string
      key(int64_t fieldindex) const override;

    bool
      haskey(const std::string& key) const override;

    const std::vector<std::string>
      keys() const override;

    // operations
    const std::string
      validityerror(const std::string& path) const override;

    const ContentPtr
      shallow_simplify() const override;

    const ContentPtr
      num(int64_t axis, int64_t depth) const override;

    const std::pair<Index64, ContentPtr>
      offsets_and_flattened(int64_t axis, int64_t depth) const override;

    bool
      mergeable(const ContentPtr& other, bool mergebool) const override;

    const ContentPtr
      merge(const ContentPtr& other) const override;

    const SliceItemPtr
      asslice() const override;

    const ContentPtr
      fillna(const ContentPtr& value) const override;

    const ContentPtr
      rpad(int64_t length, int64_t axis, int64_t depth) const override;

    const ContentPtr
      rpad_and_clip(int64_t length,
                    int64_t axis,
                    int64_t depth) const override;

    const ContentPtr
      reduce_next(const Reducer& reducer,
                  int64_t negaxis,
                  const Index64& starts,
                  const Index64& parents,
                  int64_t outlength,
                  bool mask,
                  bool keepdims) const override;

    const ContentPtr
      localindex(int64_t axis, int64_t depth) const override;

    const ContentPtr
      choose(int64_t n,
             bool diagonal,
             const util::RecordLookupPtr& recordlookup,
             const util::Parameters& parameters,
             int64_t axis,
             int64_t depth) const override;

    const ContentPtr
      getitem_next(const SliceAt& at,
                   const Slice& tail,
                   const Index64& advanced) const override;

    const ContentPtr
      getitem_next(const SliceRange& range,
                   const Slice& tail,
                   const Index64& advanced) const override;

    const ContentPtr
      getitem_next(const SliceArray64& array,
                   const Slice& tail,
                   const Index64& advanced) const override;

    const ContentPtr
      getitem_next(const SliceJagged64& jagged,
                   const Slice& tail,
                   const Index64& advanced) const override;

    const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceArray64& slicecontent,
                          const Slice& tail) const override;

    const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceMissing64& slicecontent,
                          const Slice& tail) const override;

    const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceJagged64& slicecontent,
                          const Slice& tail) const override;

  private:
    const IndexOf<T> offsets_;
    const ContentPtr content_;
  };

  using ListOffsetArray32  = ListOffsetArrayOf<int32_t>;
  using ListOffsetArrayU32 = ListOffsetArrayOf<uint32_t>;
  using ListOffsetArray64  = ListOffsetArrayOf<int64_t>;
}

#endif // AWKWARD_LISTOFFSETARRAY_H_
