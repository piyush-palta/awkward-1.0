// BSD 3-Clause License; see https://github.com/jpivarski/awkward-1.0/blob/master/LICENSE

#ifndef AWKWARD_IDENTITIES_H_
#define AWKWARD_IDENTITIES_H_

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "awkward/cpu-kernels/util.h"
#include "awkward/Index.h"

namespace awkward {
  class Identities;
  using IdentitiesPtr = std::shared_ptr<Identities>;

  class EXPORT_SYMBOL Identities {
  public:
    using Ref = int64_t;

    using FieldLoc = std::vector<std::pair<int64_t, std::string>>;

    static Ref
      newref();

    static IdentitiesPtr
      none();

    Identities(const Ref ref,
               const FieldLoc& fieldloc,
               int64_t offset,
               int64_t width,
               int64_t length);

    const Ref
      ref() const;

    const FieldLoc
      fieldloc() const;

    const int64_t
      offset() const;

    const int64_t
      width() const;

    const int64_t
      length() const;

    virtual const std::string
      classname() const = 0;

    virtual const std::string
      identity_at(int64_t where) const = 0;

    virtual const IdentitiesPtr
      to64() const = 0;

    virtual const std::string
      tostring_part(const std::string& indent,
                    const std::string& pre,
                    const std::string& post) const = 0;

    virtual const IdentitiesPtr
      getitem_range_nowrap(int64_t start, int64_t stop) const = 0;

    virtual void
      nbytes_part(std::map<size_t, int64_t>& largest) const = 0;

    virtual const IdentitiesPtr
      shallow_copy() const = 0;

    virtual const IdentitiesPtr
      deep_copy() const = 0;

    virtual const IdentitiesPtr
      getitem_carry_64(const Index64& carry) const = 0;

    virtual const IdentitiesPtr
      withfieldloc(const FieldLoc& fieldloc) const = 0;

    virtual int64_t
      value(int64_t row, int64_t col) const = 0;

    const std::string
      tostring() const;

  protected:
    const Ref ref_;
    const FieldLoc fieldloc_;
    int64_t offset_;
    int64_t width_;
    int64_t length_;
  };

  template <typename T>
  class EXPORT_SYMBOL IdentitiesOf: public Identities {
  public:
    IdentitiesOf<T>(const Ref ref,
                    const FieldLoc& fieldloc,
                    int64_t width,
                    int64_t length);

    IdentitiesOf<T>(const Ref ref,
                    const FieldLoc& fieldloc,
                    int64_t offset,
                    int64_t width,
                    int64_t length,
                    const std::shared_ptr<T> ptr);

    const std::shared_ptr<T>
      ptr() const;

    const std::string
      classname() const override;

    const std::string
      identity_at(int64_t at) const override;

    const IdentitiesPtr
      to64() const override;

    const std::string
      tostring_part(const std::string& indent,
                    const std::string& pre,
                    const std::string& post) const override;

    const IdentitiesPtr
      getitem_range_nowrap(int64_t start, int64_t stop) const override;

    void
      nbytes_part(std::map<size_t, int64_t>& largest) const override;

    const IdentitiesPtr
      shallow_copy() const override;

    const IdentitiesPtr
      deep_copy() const override;

    const IdentitiesPtr
      getitem_carry_64(const Index64& carry) const override;

    const IdentitiesPtr
      withfieldloc(const FieldLoc& fieldloc) const override;

    int64_t
      value(int64_t row, int64_t col) const override;

    const std::vector<T>
      getitem_at(int64_t at) const;

    const std::vector<T>
      getitem_at_nowrap(int64_t at) const;

    const IdentitiesPtr
      getitem_range(int64_t start, int64_t stop) const;

  private:
    const std::shared_ptr<T> ptr_;
  };

  using Identities32 = IdentitiesOf<int32_t>;
  using Identities64 = IdentitiesOf<int64_t>;
}

#endif // AWKWARD_IDENTITIES_H_
