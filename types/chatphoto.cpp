// This file generated by libqtelegram-code-generator.
// You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN

#include "chatphoto.h"
#include "core/inboundpkt.h"
#include "core/outboundpkt.h"
#include "util/tlvalues.h"

ChatPhoto::ChatPhoto(ChatPhotoType classType, InboundPkt *in) :
    m_classType(classType)
{
    if(in) fetch(in);
}

ChatPhoto::ChatPhoto(InboundPkt *in) :
    m_classType(typeChatPhotoEmpty)
{
    fetch(in);
}

ChatPhoto::~ChatPhoto() {
}

void ChatPhoto::setPhotoBig(const FileLocation &photoBig) {
    m_photoBig = photoBig;
}

FileLocation ChatPhoto::photoBig() const {
    return m_photoBig;
}

void ChatPhoto::setPhotoSmall(const FileLocation &photoSmall) {
    m_photoSmall = photoSmall;
}

FileLocation ChatPhoto::photoSmall() const {
    return m_photoSmall;
}

bool ChatPhoto::operator ==(const ChatPhoto &b) {
    return m_photoBig == b.m_photoBig &&
           m_photoSmall == b.m_photoSmall;
}

void ChatPhoto::setClassType(ChatPhoto::ChatPhotoType classType) {
    m_classType = classType;
}

ChatPhoto::ChatPhotoType ChatPhoto::classType() const {
    return m_classType;
}

bool ChatPhoto::fetch(InboundPkt *in) {
    LQTG_FETCH_LOG;
    int x = in->fetchInt();
    switch(x) {
    case typeChatPhotoEmpty: {
        m_classType = static_cast<ChatPhotoType>(x);
        return true;
    }
        break;
    
    case typeChatPhoto: {
        m_photoSmall.fetch(in);
        m_photoBig.fetch(in);
        m_classType = static_cast<ChatPhotoType>(x);
        return true;
    }
        break;
    
    default:
        LQTG_FETCH_ASSERT;
        return false;
    }
}

bool ChatPhoto::push(OutboundPkt *out) const {
    out->appendInt(m_classType);
    switch(m_classType) {
    case typeChatPhotoEmpty: {
        return true;
    }
        break;
    
    case typeChatPhoto: {
        m_photoSmall.push(out);
        m_photoBig.push(out);
        return true;
    }
        break;
    
    default:
        return false;
    }
}

