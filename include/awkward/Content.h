// BSD 3-Clause License; see https://github.com/jpivarski/awkward-1.0/blob/master/LICENSE

#ifndef AWKWARD_CONTENT_H_
#define AWKWARD_CONTENT_H_

#include <cstdio>
#include <map>

#include "awkward/cpu-kernels/util.h"
#include "awkward/Identities.h"
#include "awkward/Slice.h"
#include "awkward/io/json.h"
#include "awkward/type/Type.h"
#include "awkward/Index.h"
#include "awkward/Reducer.h"

namespace awkward {
  class Content;
  using ContentPtr    = std::shared_ptr<Content>;
  using ContentPtrVec = std::vector<std::shared_ptr<Content>>;

  class EXPORT_SYMBOL Content {
  public:
    Content(const IdentitiesPtr& identities,
            const util::Parameters& parameters);

    virtual ~Content();

    virtual bool
      isscalar() const;

    virtual const std::string
      classname() const = 0;

    virtual const IdentitiesPtr
      identities() const;

    virtual void
      setidentities() = 0;

    virtual void
      setidentities(const IdentitiesPtr& identities) = 0;

    virtual const TypePtr
      type(const util::TypeStrs& typestrs) const = 0;

    virtual const std::string
      tostring_part(const std::string& indent,
                    const std::string& pre,
                    const std::string& post) const = 0;

    virtual void
      tojson_part(ToJson& builder) const = 0;

    virtual void
      nbytes_part(std::map<size_t, int64_t>& largest) const = 0;

    virtual int64_t
      length() const = 0;

    virtual const ContentPtr
      shallow_copy() const = 0;

    virtual const ContentPtr
      deep_copy(bool copyarrays,
                bool copyindexes,
                bool copyidentities) const = 0;

    virtual void
      check_for_iteration() const = 0;

    virtual const ContentPtr
      getitem_nothing() const = 0;

    virtual const ContentPtr
      getitem_at(int64_t at) const = 0;

    virtual const ContentPtr
      getitem_at_nowrap(int64_t at) const = 0;

    virtual const ContentPtr
      getitem_range(int64_t start, int64_t stop) const = 0;

    virtual const ContentPtr
      getitem_range_nowrap(int64_t start, int64_t stop) const = 0;

    virtual const ContentPtr
      getitem_field(const std::string& key) const = 0;

    virtual const ContentPtr
      getitem_fields(const std::vector<std::string>& keys) const = 0;

    virtual const ContentPtr
      getitem(const Slice& where) const;

    virtual const ContentPtr
      getitem_next(const SliceItemPtr& head,
                   const Slice& tail,
                   const Index64& advanced) const;

    virtual const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceItemPtr& slicecontent,
                          const Slice& tail) const;

    virtual const ContentPtr
      carry(const Index64& carry) const = 0;

    virtual const std::string
      purelist_parameter(const std::string& key) const = 0;

    virtual bool
      purelist_isregular() const = 0;

    virtual int64_t
      purelist_depth() const = 0;

    virtual const std::pair<int64_t, int64_t>
      minmax_depth() const = 0;

    virtual const std::pair<bool, int64_t>
      branch_depth() const = 0;

    virtual int64_t
      numfields() const = 0;

    virtual int64_t
      fieldindex(const std::string& key) const = 0;

    virtual const std::string
      key(int64_t fieldindex) const = 0;

    virtual bool
      haskey(const std::string& key) const = 0;

    virtual const std::vector<std::string>
      keys() const = 0;

    // operations
    virtual const std::string
      validityerror(const std::string& path) const = 0;

    virtual const ContentPtr
      shallow_simplify() const = 0;

    virtual const ContentPtr
      num(int64_t axis, int64_t depth) const = 0;

    virtual const std::pair<Index64, ContentPtr>
      offsets_and_flattened(int64_t axis, int64_t depth) const = 0;

    virtual bool
      mergeable(const ContentPtr& other, bool mergebool) const = 0;

    virtual const ContentPtr
      merge(const ContentPtr& other) const = 0;

    virtual const SliceItemPtr
      asslice() const = 0;

    virtual const ContentPtr
      fillna(const ContentPtr& value) const = 0;

    virtual const ContentPtr
      rpad(int64_t length, int64_t axis, int64_t depth) const = 0;

    virtual const ContentPtr
      rpad_and_clip(int64_t length, int64_t axis, int64_t depth) const = 0;

    virtual const ContentPtr
      reduce_next(const Reducer& reducer,
                  int64_t negaxis,
                  const Index64& starts,
                  const Index64& parents,
                  int64_t outlength,
                  bool mask,
                  bool keepdims) const = 0;

    virtual const ContentPtr
      localindex(int64_t axis, int64_t depth) const = 0;

    virtual const ContentPtr
      choose(int64_t n,
             bool diagonal,
             const util::RecordLookupPtr& recordlookup,
             const util::Parameters& parameters,
             int64_t axis,
             int64_t depth) const = 0;

    const std::string
      tostring() const;

    const std::string
      tojson(bool pretty, int64_t maxdecimals) const;

    void
      tojson(FILE* destination,
             bool pretty,
             int64_t maxdecimals,
             int64_t buffersize) const;

    int64_t
      nbytes() const;

    const ContentPtr
      reduce(const Reducer& reducer,
             int64_t axis,
             bool mask,
             bool keepdims) const;

    const util::Parameters
      parameters() const;

    void
      setparameters(const util::Parameters& parameters);

    const std::string
      parameter(const std::string& key) const;

    void
      setparameter(const std::string& key, const std::string& value);

    bool
      parameter_equals(const std::string& key, const std::string& value) const;

    bool
      parameters_equal(const util::Parameters& other) const;

    const ContentPtr
      merge_as_union(const ContentPtr& other) const;

    const ContentPtr
      rpad_axis0(int64_t target, bool clip) const;

    const ContentPtr
      localindex_axis0() const;

    const ContentPtr
      choose_axis0(int64_t n,
                   bool diagonal,
                   const util::RecordLookupPtr& recordlookup,
                   const util::Parameters& parameters) const;

    virtual const ContentPtr
      getitem_next(const SliceAt& at,
                   const Slice& tail,
                   const Index64& advanced) const = 0;

    virtual const ContentPtr
      getitem_next(const SliceRange& range,
                   const Slice& tail,
                   const Index64& advanced) const = 0;

    virtual const ContentPtr
      getitem_next(const SliceEllipsis& ellipsis,
                   const Slice& tail,
                   const Index64& advanced) const;

    virtual const ContentPtr
      getitem_next(const SliceNewAxis& newaxis,
                   const Slice& tail,
                   const Index64& advanced) const;

    virtual const ContentPtr
      getitem_next(const SliceArray64& array,
                   const Slice& tail,
                   const Index64& advanced) const = 0;

    virtual const ContentPtr
      getitem_next(const SliceField& field,
                   const Slice& tail,
                   const Index64& advanced) const;

    virtual const ContentPtr
      getitem_next(const SliceFields& fields,
                   const Slice& tail,
                   const Index64& advanced) const;

    virtual const ContentPtr
      getitem_next(const SliceMissing64& missing,
                   const Slice& tail,
                   const Index64& advanced) const;

    virtual const ContentPtr
      getitem_next(const SliceJagged64& jagged,
                   const Slice& tail,
                   const Index64& advanced) const = 0;

    virtual const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceArray64& slicecontent,
                          const Slice& tail) const = 0;

    virtual const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceMissing64& slicecontent,
                          const Slice& tail) const = 0;

    virtual const ContentPtr
      getitem_next_jagged(const Index64& slicestarts,
                          const Index64& slicestops,
                          const SliceJagged64& slicecontent,
                          const Slice& tail) const = 0;

  protected:
    const ContentPtr
      getitem_next_array_wrap(const ContentPtr& outcontent,
                              const std::vector<int64_t>& shape) const;

    const std::string
      parameters_tostring(const std::string& indent,
                          const std::string& pre,
                          const std::string& post) const;

    const int64_t
      axis_wrap_if_negative(int64_t axis) const;

  protected:
    IdentitiesPtr identities_;
    util::Parameters parameters_;
  };
}

#endif // AWKWARD_CONTENT_H_
