// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_lazy_dependencies.proto

#ifndef PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto
#define PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto

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
#include <google/protobuf/unittest_lazy_dependencies_custom_option.pb.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto 

namespace protobuf_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[3];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto
namespace protobuf_unittest {
namespace lazy_imports {
class ImportedMessage;
class ImportedMessageDefaultTypeInternal;
extern ImportedMessageDefaultTypeInternal _ImportedMessage_default_instance_;
class MessageCustomOption;
class MessageCustomOptionDefaultTypeInternal;
extern MessageCustomOptionDefaultTypeInternal _MessageCustomOption_default_instance_;
class MessageCustomOption2;
class MessageCustomOption2DefaultTypeInternal;
extern MessageCustomOption2DefaultTypeInternal _MessageCustomOption2_default_instance_;
}  // namespace lazy_imports
}  // namespace protobuf_unittest
namespace google {
namespace protobuf {
template<> ::protobuf_unittest::lazy_imports::ImportedMessage* Arena::CreateMaybeMessage<::protobuf_unittest::lazy_imports::ImportedMessage>(Arena*);
template<> ::protobuf_unittest::lazy_imports::MessageCustomOption* Arena::CreateMaybeMessage<::protobuf_unittest::lazy_imports::MessageCustomOption>(Arena*);
template<> ::protobuf_unittest::lazy_imports::MessageCustomOption2* Arena::CreateMaybeMessage<::protobuf_unittest::lazy_imports::MessageCustomOption2>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace protobuf_unittest {
namespace lazy_imports {

// ===================================================================

class ImportedMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:protobuf_unittest.lazy_imports.ImportedMessage) */ {
 public:
  ImportedMessage();
  virtual ~ImportedMessage();

  ImportedMessage(const ImportedMessage& from);

  inline ImportedMessage& operator=(const ImportedMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ImportedMessage(ImportedMessage&& from) noexcept
    : ImportedMessage() {
    *this = ::std::move(from);
  }

  inline ImportedMessage& operator=(ImportedMessage&& from) noexcept {
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

  inline ::google::protobuf::Arena* GetArena() const final {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const final {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor();
  static const ImportedMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ImportedMessage* internal_default_instance() {
    return reinterpret_cast<const ImportedMessage*>(
               &_ImportedMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void UnsafeArenaSwap(ImportedMessage* other);
  void Swap(ImportedMessage* other);
  friend void swap(ImportedMessage& a, ImportedMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ImportedMessage* New() const final {
    return CreateMaybeMessage<ImportedMessage>(NULL);
  }

  ImportedMessage* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ImportedMessage>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ImportedMessage& from);
  void MergeFrom(const ImportedMessage& from);
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
  void InternalSwap(ImportedMessage* other);
  protected:
  explicit ImportedMessage(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .protobuf_unittest.lazy_imports.LazyMessage lazy_message = 1;
  bool has_lazy_message() const;
  void clear_lazy_message();
  static const int kLazyMessageFieldNumber = 1;
  private:
  const ::protobuf_unittest::lazy_imports::LazyMessage& _internal_lazy_message() const;
  public:
  const ::protobuf_unittest::lazy_imports::LazyMessage& lazy_message() const;
  ::protobuf_unittest::lazy_imports::LazyMessage* release_lazy_message();
  ::protobuf_unittest::lazy_imports::LazyMessage* mutable_lazy_message();
  void set_allocated_lazy_message(::protobuf_unittest::lazy_imports::LazyMessage* lazy_message);
  void unsafe_arena_set_allocated_lazy_message(
      ::protobuf_unittest::lazy_imports::LazyMessage* lazy_message);
  ::protobuf_unittest::lazy_imports::LazyMessage* unsafe_arena_release_lazy_message();

  // @@protoc_insertion_point(class_scope:protobuf_unittest.lazy_imports.ImportedMessage)
 private:
  void set_has_lazy_message();
  void clear_has_lazy_message();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::protobuf_unittest::lazy_imports::LazyMessage* lazy_message_;
  friend struct ::protobuf_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class MessageCustomOption : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:protobuf_unittest.lazy_imports.MessageCustomOption) */ {
 public:
  MessageCustomOption();
  virtual ~MessageCustomOption();

  MessageCustomOption(const MessageCustomOption& from);

  inline MessageCustomOption& operator=(const MessageCustomOption& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MessageCustomOption(MessageCustomOption&& from) noexcept
    : MessageCustomOption() {
    *this = ::std::move(from);
  }

  inline MessageCustomOption& operator=(MessageCustomOption&& from) noexcept {
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

  inline ::google::protobuf::Arena* GetArena() const final {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const final {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageCustomOption& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageCustomOption* internal_default_instance() {
    return reinterpret_cast<const MessageCustomOption*>(
               &_MessageCustomOption_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void UnsafeArenaSwap(MessageCustomOption* other);
  void Swap(MessageCustomOption* other);
  friend void swap(MessageCustomOption& a, MessageCustomOption& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MessageCustomOption* New() const final {
    return CreateMaybeMessage<MessageCustomOption>(NULL);
  }

  MessageCustomOption* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<MessageCustomOption>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const MessageCustomOption& from);
  void MergeFrom(const MessageCustomOption& from);
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
  void InternalSwap(MessageCustomOption* other);
  protected:
  explicit MessageCustomOption(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:protobuf_unittest.lazy_imports.MessageCustomOption)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class MessageCustomOption2 : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:protobuf_unittest.lazy_imports.MessageCustomOption2) */ {
 public:
  MessageCustomOption2();
  virtual ~MessageCustomOption2();

  MessageCustomOption2(const MessageCustomOption2& from);

  inline MessageCustomOption2& operator=(const MessageCustomOption2& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MessageCustomOption2(MessageCustomOption2&& from) noexcept
    : MessageCustomOption2() {
    *this = ::std::move(from);
  }

  inline MessageCustomOption2& operator=(MessageCustomOption2&& from) noexcept {
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

  inline ::google::protobuf::Arena* GetArena() const final {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const final {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor();
  static const MessageCustomOption2& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MessageCustomOption2* internal_default_instance() {
    return reinterpret_cast<const MessageCustomOption2*>(
               &_MessageCustomOption2_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void UnsafeArenaSwap(MessageCustomOption2* other);
  void Swap(MessageCustomOption2* other);
  friend void swap(MessageCustomOption2& a, MessageCustomOption2& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MessageCustomOption2* New() const final {
    return CreateMaybeMessage<MessageCustomOption2>(NULL);
  }

  MessageCustomOption2* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<MessageCustomOption2>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const MessageCustomOption2& from);
  void MergeFrom(const MessageCustomOption2& from);
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
  void InternalSwap(MessageCustomOption2* other);
  protected:
  explicit MessageCustomOption2(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:protobuf_unittest.lazy_imports.MessageCustomOption2)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ImportedMessage

// optional .protobuf_unittest.lazy_imports.LazyMessage lazy_message = 1;
inline bool ImportedMessage::has_lazy_message() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ImportedMessage::set_has_lazy_message() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ImportedMessage::clear_has_lazy_message() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::protobuf_unittest::lazy_imports::LazyMessage& ImportedMessage::_internal_lazy_message() const {
  return *lazy_message_;
}
inline const ::protobuf_unittest::lazy_imports::LazyMessage& ImportedMessage::lazy_message() const {
  const ::protobuf_unittest::lazy_imports::LazyMessage* p = lazy_message_;
  // @@protoc_insertion_point(field_get:protobuf_unittest.lazy_imports.ImportedMessage.lazy_message)
  return p != NULL ? *p : *reinterpret_cast<const ::protobuf_unittest::lazy_imports::LazyMessage*>(
      &::protobuf_unittest::lazy_imports::_LazyMessage_default_instance_);
}
inline ::protobuf_unittest::lazy_imports::LazyMessage* ImportedMessage::release_lazy_message() {
  // @@protoc_insertion_point(field_release:protobuf_unittest.lazy_imports.ImportedMessage.lazy_message)
  clear_has_lazy_message();
  ::protobuf_unittest::lazy_imports::LazyMessage* temp = lazy_message_;
  if (GetArenaNoVirtual() != NULL) {
    temp = ::google::protobuf::internal::DuplicateIfNonNull(temp);
  }
  lazy_message_ = NULL;
  return temp;
}
inline ::protobuf_unittest::lazy_imports::LazyMessage* ImportedMessage::unsafe_arena_release_lazy_message() {
  // @@protoc_insertion_point(field_unsafe_arena_release:protobuf_unittest.lazy_imports.ImportedMessage.lazy_message)
  clear_has_lazy_message();
  ::protobuf_unittest::lazy_imports::LazyMessage* temp = lazy_message_;
  lazy_message_ = NULL;
  return temp;
}
inline ::protobuf_unittest::lazy_imports::LazyMessage* ImportedMessage::mutable_lazy_message() {
  set_has_lazy_message();
  if (lazy_message_ == NULL) {
    auto* p = CreateMaybeMessage<::protobuf_unittest::lazy_imports::LazyMessage>(GetArenaNoVirtual());
    lazy_message_ = p;
  }
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.lazy_imports.ImportedMessage.lazy_message)
  return lazy_message_;
}
inline void ImportedMessage::set_allocated_lazy_message(::protobuf_unittest::lazy_imports::LazyMessage* lazy_message) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(lazy_message_);
  }
  if (lazy_message) {
    ::google::protobuf::Arena* submessage_arena =
      reinterpret_cast<::google::protobuf::MessageLite*>(lazy_message)->GetArena();
    if (message_arena != submessage_arena) {
      lazy_message = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, lazy_message, submessage_arena);
    }
    set_has_lazy_message();
  } else {
    clear_has_lazy_message();
  }
  lazy_message_ = lazy_message;
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.lazy_imports.ImportedMessage.lazy_message)
}

// -------------------------------------------------------------------

// MessageCustomOption

// -------------------------------------------------------------------

// MessageCustomOption2

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace lazy_imports
}  // namespace protobuf_unittest

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flazy_5fdependencies_2eproto
