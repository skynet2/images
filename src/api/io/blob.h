#pragma once

#include <vips/vips8>

namespace weserv::api::io {

class Blob {
 public:
    explicit Blob(VipsBlob *blob = nullptr) : blob_(blob) {}

    // copy constructor
    Blob(const Blob &a) : blob_(a.blob_) {
        reference();
    }

    // this mustn't be virtual: we want this class to only be a pointer,
    // no vtable allowed
    ~Blob() {
        unreference();
    }

    // assignment ... we must delete the old ref
    Blob &operator=(const Blob &a) {
        // check whether we are already referencing this object -
        // if so make this a null op. This will also deal with
        // self-assignment.
        if (blob_ != a.blob_) {
            unreference();

            blob_ = a.blob_;

            reference();
        }

        return *this;
    }

    /**
     * Get the underlying VipsBlob pointer.
     * @return The underlying VipsBlob pointer.
     */
    VipsBlob *get_blob() const {
        return blob_;
    }

    /**
     * Get the data from a Blob.
     * @param length Return number of bytes of data.
     * @return The data.
     */
    const void *get_blob(size_t *length) const {
        return vips_blob_get(blob_, length);
    }

    /**
     * @return true if this Blob is a nullptr.
     */
    bool is_null() const {
        return blob_ == nullptr;
    }

 private:
    /**
     * The underlying VipsBlob pointer, can be nullptr.
     */
    VipsBlob *blob_;

    inline void unreference() {
        if (blob_ != nullptr) {
            vips_area_unref(reinterpret_cast<VipsArea *>(blob_));
        }
    }

    inline void reference() {
        if (blob_ != nullptr) {
            vips_area_copy(reinterpret_cast<VipsArea *>(blob_));
        }
    }
};

}  // namespace weserv::api::io
