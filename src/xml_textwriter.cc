// Copyright 2011, Squish Tech, LLC.

#include "libxmljs.h"
#include "xml_textwriter.h"

namespace libxmljs {

XmlTextWriter::XmlTextWriter() {
  textWriter = NULL;
  writerBuffer = NULL;
}

XmlTextWriter::~XmlTextWriter() {
  if (textWriter) {
    xmlFreeTextWriter(textWriter);
  }
  if (writerBuffer) {
    xmlBufferFree(writerBuffer);
  }
}

NAN_METHOD(XmlTextWriter::NewTextWriter) {
  NanScope();
  XmlTextWriter *writer = new XmlTextWriter();
  writer->Wrap(args.Holder());

  NanReturnValue(args.Holder());
}

NAN_METHOD(XmlTextWriter::OpenMemory) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  writer->writerBuffer = xmlBufferCreate();
  if (!writer->writerBuffer) {
    return NanThrowError("Failed to create memory buffer");
  }

  writer->textWriter = xmlNewTextWriterMemory(writer->writerBuffer, 0);
  if (!writer->textWriter) {
    xmlBufferFree(writer->writerBuffer);
    return NanThrowError("Failed to create buffer writer");
  }

  NanReturnValue(NanUndefined());
}

NAN_METHOD(XmlTextWriter::BufferContent) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  // Flush the output buffer of the libxml writer instance in order to push all
  // the content to our writerBuffer.
  xmlTextWriterFlush(writer->textWriter);

  // Receive bytes from the writerBuffer
  const xmlChar *buf = xmlBufferContent(writer->writerBuffer);

  NanReturnValue(NanNew<v8::String>((const char*)buf));
}

NAN_METHOD(XmlTextWriter::BufferEmpty) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  // Flush the output buffer of the libxml writer instance in order to push all
  // the content to our writerBuffer.
  xmlTextWriterFlush(writer->textWriter);

  // Clear the memory buffer
  xmlBufferEmpty(writer->writerBuffer);

  NanReturnValue(NanUndefined());
}

NAN_METHOD(XmlTextWriter::StartDocument) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  v8::String::Utf8Value version(args[0]->ToString());
  v8::String::Utf8Value encoding(args[1]->ToString());
  v8::String::Utf8Value standalone(args[2]->ToString());

  int result = xmlTextWriterStartDocument(
          writer->textWriter,
          args[0]->IsUndefined() ? NULL : *version,
          args[1]->IsUndefined() ? NULL : *encoding,
          args[2]->IsUndefined() ? NULL : *standalone);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::EndDocument) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  int result = xmlTextWriterEndDocument(writer->textWriter);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::StartElementNS) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  v8::String::Utf8Value prefix(args[0]->ToString());
  v8::String::Utf8Value name(args[1]->ToString());
  v8::String::Utf8Value namespaceURI(args[2]->ToString());

  int result = xmlTextWriterStartElementNS(
          writer->textWriter,
          args[0]->IsUndefined() ? NULL : (const xmlChar*)*prefix,
          args[1]->IsUndefined() ? NULL : (const xmlChar*)*name,
          args[2]->IsUndefined() ? NULL : (const xmlChar*)*namespaceURI);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::EndElement) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  int result = xmlTextWriterEndElement(writer->textWriter);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::StartAttributeNS) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  v8::String::Utf8Value prefix(args[0]->ToString());
  v8::String::Utf8Value name(args[1]->ToString());
  v8::String::Utf8Value namespaceURI(args[2]->ToString());

  int result = xmlTextWriterStartAttributeNS(
          writer->textWriter,
          args[0]->IsUndefined() ? NULL : (const xmlChar*)*prefix,
          args[1]->IsUndefined() ? NULL : (const xmlChar*)*name,
          args[2]->IsUndefined() ? NULL : (const xmlChar*)*namespaceURI);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::EndAttribute) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  int result = xmlTextWriterEndAttribute(writer->textWriter);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::StartCdata) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  int result = xmlTextWriterStartCDATA(writer->textWriter);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::EndCdata) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  int result = xmlTextWriterEndCDATA(writer->textWriter);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::StartComment) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  int result = xmlTextWriterStartComment(writer->textWriter);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::EndComment) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  int result = xmlTextWriterEndComment(writer->textWriter);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

NAN_METHOD(XmlTextWriter::WriteString) {
  NanScope();

  XmlTextWriter *writer = ObjectWrap::Unwrap<XmlTextWriter>(args.Holder());

  v8::String::Utf8Value string(args[0]->ToString());

  int result = xmlTextWriterWriteString(writer->textWriter,
      (const xmlChar*)*string);

  NanReturnValue(NanNew<v8::Number>((double)result));
}

void
XmlTextWriter::Initialize(v8::Handle<v8::Object> target) {
  NanScope();

  v8::Local<v8::FunctionTemplate> writer_t =
    NanNew<v8::FunctionTemplate>(NewTextWriter);

  v8::Persistent<v8::FunctionTemplate> xml_writer_template;
  NanAssignPersistent(xml_writer_template, writer_t);


  writer_t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_openMemory",
          XmlTextWriter::OpenMemory);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_bufferContent",
          XmlTextWriter::BufferContent);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_bufferEmpty",
          XmlTextWriter::BufferEmpty);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_startDocument",
          XmlTextWriter::StartDocument);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_endDocument",
          XmlTextWriter::EndDocument);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_startElementNS",
          XmlTextWriter::StartElementNS);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_endElement",
          XmlTextWriter::EndElement);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_startAttributeNS",
          XmlTextWriter::StartAttributeNS);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_endAttribute",
          XmlTextWriter::EndAttribute);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_startCdata",
          XmlTextWriter::StartCdata);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_endCdata",
          XmlTextWriter::EndCdata);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_startComment",
          XmlTextWriter::StartComment);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_endComment",
          XmlTextWriter::EndComment);

  NODE_SET_PROTOTYPE_METHOD(writer_t,
          "_writeString",
          XmlTextWriter::WriteString);

  target->Set(NanNew<v8::String>("TextWriter"),
              writer_t->GetFunction());
}
}  // namespace libxmljs
