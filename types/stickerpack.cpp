// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#include "stickerpack.h"
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "util/tlvalues.h"

StickerPack::StickerPack(StickerPackType classType, InboundPkt *in) :
    m_classType(classType)
{
    if(in) fetch(in);
}

StickerPack::StickerPack(InboundPkt *in) :
    m_classType(typeStickerPack)
{
    fetch(in);
}

StickerPack::~StickerPack() {
}

void StickerPack::setDocuments(const QList<qint64> &documents) {
    m_documents = documents;
}

QList<qint64> StickerPack::documents() const {
    return m_documents;
}

void StickerPack::setEmoticon(const QString &emoticon) {
    m_emoticon = emoticon;
}

QString StickerPack::emoticon() const {
    return m_emoticon;
}

bool StickerPack::operator ==(const StickerPack &b) {
    return m_documents == b.m_documents &&
           m_emoticon == b.m_emoticon;
}

void StickerPack::setClassType(StickerPack::StickerPackType classType) {
    m_classType = classType;
}

StickerPack::StickerPackType StickerPack::classType() const {
    return m_classType;
}

bool StickerPack::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeStickerPack: {
        m_emoticon = in->fetchQString();
        if(in->fetchInt() != (qint32)TL_Vector) return false;
        qint32 m_documents_length = in->fetchInt();
        m_documents.clear();
        for (qint32 i = 0; i < m_documents_length; i++) {
            qint64 type;
            type = in->fetchLong();
            m_documents.append(type);
        }
        m_classType = static_cast<StickerPackType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

bool StickerPack::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeStickerPack: {
        out->appendQString(m_emoticon);
        out->appendInt(TL_Vector);
        out->appendInt(m_documents.count());
        for (qint32 i = 0; i < m_documents.count(); i++) {
            out->appendLong(m_documents[i]);
        }
        return true;
    }
        break;
    
    default:
        return false;
    }
}

