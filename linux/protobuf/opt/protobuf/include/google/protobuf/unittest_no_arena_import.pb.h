// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_no_arena_import.proto

#ifndef PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fno_5farena_5fimport_2eproto
#define PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fno_5farena_5fimport_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_google_2fprotobuf_2funittest_5fno_5farena_5fimport_2eproto 

namespace protobuf_google_2fprotobuf_2funittest_5fno_5farena_5fimport_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_google_2fprotobuf_2funittest_5fno_5farena_5fimport_2eproto
namespace proto2_arena_unittest {
class ImportNoArenaNestedMessage;
class ImportNoArenaNestedMessageDefaultTypeInternal;
extern ImportNoArenaNestedMessageDefaultTypeInternal _ImportNoArenaNestedMessage_default_instance_;
}  // namespace proto2_arena_unittest
namespace google {
namespace protobuf {
template<> ::proto2_arena_unittest::ImportNoArenaNestedMessage* Arena::CreateMaybeMessage<::proto2_arena_unittest::ImportNoArenaNestedMessage>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace proto2_arena_unittest {

// ===================================================================

class ImportNoArenaNestedMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto2_arena_unittest.ImportNoArenaNestedMessage) */ {
 public:
  ImportNoArenaNestedMessage();
  virtual ~ImportNoArenaNestedMessage();

  ImportNoArenaNestedMessage(const ImportNoArenaNestedMessage& from);

  inline ImportNoArenaNestedMessage& operator=(const ImportNoArenaNestedMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ImportNoArenaNestedMessage(ImportNoArenaNestedMessage&& from) noexcept
    : ImportNoArenaNestedMessage() {
    *this = ::std::move(from);
  }

  inline ImportNoArenaNestedMessage& operator=(ImportNoArenaNestedMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ImportNoArenaNestedMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ImportNoArenaNestedMessage* internal_default_instance() {
    return reinterpret_cast<const ImportNoArenaNestedMessage*>(
               &_ImportNoArenaNestedMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(ImportNoArenaNestedMessage* other);
  friend void swap(ImportNoArenaNestedMessage& a, ImportNoArenaNestedMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ImportNoArenaNestedMessage* New() const final {
    return CreateMaybeMessage<ImportNoArenaNestedMessage>(NULL);
  }

  ImportNoArenaNestedMessage* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ImportNoArenaNestedMessage>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ImportNoArenaNestedMessage& from);
  void MergeFrom(const ImportNoArenaNestedMessage& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ImportNoArenaNestedMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 d = 1;
  bool has_d() const;
  void clear_d();
  static const int kDFieldNumber = 1;
  ::google::protobuf::int32 d() const;
  void set_d(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:proto2_arena_unittest.ImportNoArenaNestedMessage)
 private:
  void set_has_d();
  void clear_has_d();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::int32 d_;
  friend struct ::protobuf_google_2fprotobuf_2funittest_5fno_5farena_5fimport_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ImportNoArenaNestedMessage

// optional int32 d = 1;
inline bool ImportNoArenaNestedMessage::has_d() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ImportNoArenaNestedMessage::set_has_d() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ImportNoArenaNestedMessage::clear_has_d() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ImportNoArenaNestedMessage::clear_d() {
  d_ = 0;
  clear_has_d();
}
inline ::google::protobuf::int32 ImportNoArenaNestedMessage::d() const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.ImportNoArenaNestedMessage.d)
  return d_;
}
inline void ImportNoArenaNestedMessage::set_d(::google::protobuf::int32 value) {
  set_has_d();
  d_ = value;
  // @@protoc_insertion_point(field_set:proto2_arena_unittest.ImportNoArenaNestedMessage.d)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto2_arena_unittest

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fno_5farena_5fimport_2eproto
