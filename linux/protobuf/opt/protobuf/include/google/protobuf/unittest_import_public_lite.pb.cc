// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import_public_lite.proto

#include <google/protobuf/unittest_import_public_lite.pb.h>

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace protobuf_unittest_import {
class PublicImportMessageLiteDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<PublicImportMessageLite>
      _instance;
} _PublicImportMessageLite_default_instance_;
}  // namespace protobuf_unittest_import
namespace protobuf_google_2fprotobuf_2funittest_5fimport_5fpublic_5flite_2eproto {
static void InitDefaultsPublicImportMessageLite() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::protobuf_unittest_import::_PublicImportMessageLite_default_instance_;
    new (ptr) ::protobuf_unittest_import::PublicImportMessageLite();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::protobuf_unittest_import::PublicImportMessageLite::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_PublicImportMessageLite =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsPublicImportMessageLite}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_PublicImportMessageLite.base);
}

}  // namespace protobuf_google_2fprotobuf_2funittest_5fimport_5fpublic_5flite_2eproto
namespace protobuf_unittest_import {

// ===================================================================

void PublicImportMessageLite::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PublicImportMessageLite::kEFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PublicImportMessageLite::PublicImportMessageLite()
  : ::google::protobuf::MessageLite(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_google_2fprotobuf_2funittest_5fimport_5fpublic_5flite_2eproto::scc_info_PublicImportMessageLite.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:protobuf_unittest_import.PublicImportMessageLite)
}
PublicImportMessageLite::PublicImportMessageLite(const PublicImportMessageLite& from)
  : ::google::protobuf::MessageLite(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  e_ = from.e_;
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest_import.PublicImportMessageLite)
}

void PublicImportMessageLite::SharedCtor() {
  e_ = 0;
}

PublicImportMessageLite::~PublicImportMessageLite() {
  // @@protoc_insertion_point(destructor:protobuf_unittest_import.PublicImportMessageLite)
  SharedDtor();
}

void PublicImportMessageLite::SharedDtor() {
}

void PublicImportMessageLite::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const PublicImportMessageLite& PublicImportMessageLite::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_google_2fprotobuf_2funittest_5fimport_5fpublic_5flite_2eproto::scc_info_PublicImportMessageLite.base);
  return *internal_default_instance();
}


void PublicImportMessageLite::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest_import.PublicImportMessageLite)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  e_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool PublicImportMessageLite::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::google::protobuf::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:protobuf_unittest_import.PublicImportMessageLite)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 e = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          set_has_e();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &e_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:protobuf_unittest_import.PublicImportMessageLite)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:protobuf_unittest_import.PublicImportMessageLite)
  return false;
#undef DO_
}

void PublicImportMessageLite::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:protobuf_unittest_import.PublicImportMessageLite)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 e = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->e(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:protobuf_unittest_import.PublicImportMessageLite)
}

size_t PublicImportMessageLite::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest_import.PublicImportMessageLite)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  // optional int32 e = 1;
  if (has_e()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->e());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PublicImportMessageLite::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const PublicImportMessageLite*>(&from));
}

void PublicImportMessageLite::MergeFrom(const PublicImportMessageLite& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest_import.PublicImportMessageLite)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_e()) {
    set_e(from.e());
  }
}

void PublicImportMessageLite::CopyFrom(const PublicImportMessageLite& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest_import.PublicImportMessageLite)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PublicImportMessageLite::IsInitialized() const {
  return true;
}

void PublicImportMessageLite::Swap(PublicImportMessageLite* other) {
  if (other == this) return;
  InternalSwap(other);
}
void PublicImportMessageLite::InternalSwap(PublicImportMessageLite* other) {
  using std::swap;
  swap(e_, other->e_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::std::string PublicImportMessageLite::GetTypeName() const {
  return "protobuf_unittest_import.PublicImportMessageLite";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest_import
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::protobuf_unittest_import::PublicImportMessageLite* Arena::CreateMaybeMessage< ::protobuf_unittest_import::PublicImportMessageLite >(Arena* arena) {
  return Arena::CreateInternal< ::protobuf_unittest_import::PublicImportMessageLite >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
