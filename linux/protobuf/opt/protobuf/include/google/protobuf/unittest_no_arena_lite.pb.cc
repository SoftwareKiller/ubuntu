// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_no_arena_lite.proto

#include <google/protobuf/unittest_no_arena_lite.pb.h>

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

namespace protobuf_unittest_no_arena {
class ForeignMessageLiteDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ForeignMessageLite>
      _instance;
} _ForeignMessageLite_default_instance_;
}  // namespace protobuf_unittest_no_arena
namespace protobuf_google_2fprotobuf_2funittest_5fno_5farena_5flite_2eproto {
static void InitDefaultsForeignMessageLite() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::protobuf_unittest_no_arena::_ForeignMessageLite_default_instance_;
    new (ptr) ::protobuf_unittest_no_arena::ForeignMessageLite();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::protobuf_unittest_no_arena::ForeignMessageLite::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_ForeignMessageLite =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsForeignMessageLite}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_ForeignMessageLite.base);
}

}  // namespace protobuf_google_2fprotobuf_2funittest_5fno_5farena_5flite_2eproto
namespace protobuf_unittest_no_arena {

// ===================================================================

void ForeignMessageLite::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ForeignMessageLite::kCFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ForeignMessageLite::ForeignMessageLite()
  : ::google::protobuf::MessageLite(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_google_2fprotobuf_2funittest_5fno_5farena_5flite_2eproto::scc_info_ForeignMessageLite.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:protobuf_unittest_no_arena.ForeignMessageLite)
}
ForeignMessageLite::ForeignMessageLite(const ForeignMessageLite& from)
  : ::google::protobuf::MessageLite(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  c_ = from.c_;
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest_no_arena.ForeignMessageLite)
}

void ForeignMessageLite::SharedCtor() {
  c_ = 0;
}

ForeignMessageLite::~ForeignMessageLite() {
  // @@protoc_insertion_point(destructor:protobuf_unittest_no_arena.ForeignMessageLite)
  SharedDtor();
}

void ForeignMessageLite::SharedDtor() {
}

void ForeignMessageLite::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ForeignMessageLite& ForeignMessageLite::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_google_2fprotobuf_2funittest_5fno_5farena_5flite_2eproto::scc_info_ForeignMessageLite.base);
  return *internal_default_instance();
}


void ForeignMessageLite::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest_no_arena.ForeignMessageLite)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  c_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool ForeignMessageLite::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::google::protobuf::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:protobuf_unittest_no_arena.ForeignMessageLite)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 c = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          set_has_c();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &c_)));
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
  // @@protoc_insertion_point(parse_success:protobuf_unittest_no_arena.ForeignMessageLite)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:protobuf_unittest_no_arena.ForeignMessageLite)
  return false;
#undef DO_
}

void ForeignMessageLite::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:protobuf_unittest_no_arena.ForeignMessageLite)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 c = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->c(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:protobuf_unittest_no_arena.ForeignMessageLite)
}

size_t ForeignMessageLite::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest_no_arena.ForeignMessageLite)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  // optional int32 c = 1;
  if (has_c()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->c());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ForeignMessageLite::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ForeignMessageLite*>(&from));
}

void ForeignMessageLite::MergeFrom(const ForeignMessageLite& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest_no_arena.ForeignMessageLite)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_c()) {
    set_c(from.c());
  }
}

void ForeignMessageLite::CopyFrom(const ForeignMessageLite& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest_no_arena.ForeignMessageLite)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ForeignMessageLite::IsInitialized() const {
  return true;
}

void ForeignMessageLite::Swap(ForeignMessageLite* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ForeignMessageLite::InternalSwap(ForeignMessageLite* other) {
  using std::swap;
  swap(c_, other->c_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::std::string ForeignMessageLite::GetTypeName() const {
  return "protobuf_unittest_no_arena.ForeignMessageLite";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest_no_arena
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::protobuf_unittest_no_arena::ForeignMessageLite* Arena::CreateMaybeMessage< ::protobuf_unittest_no_arena::ForeignMessageLite >(Arena* arena) {
  return Arena::CreateInternal< ::protobuf_unittest_no_arena::ForeignMessageLite >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
