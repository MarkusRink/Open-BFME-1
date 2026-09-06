// cl: /DNDEBUG /MD /EHsc
// Retail 0x00673580. The caller at ConnectionManager::getFrameCommandList
// identifies this method as NetCommandList::appendList.

class NetCommandMsg;

// BFME keeps NetCommandRef without the reference header's vptr. The three
// links therefore start at zero, four, and eight, with relay at twelve.
class NetCommandRef
{
public:
    NetCommandMsg *m_msg;
    NetCommandRef *m_next;
    NetCommandRef *m_prev;
    unsigned char m_relay;
};

class NetCommandList
{
public:
    void appendList(NetCommandList *list);
    NetCommandRef *addMessage(NetCommandMsg *message);

private:
    void *m_vptr;
    NetCommandRef *m_first;
    NetCommandRef *m_last;
    NetCommandRef *m_lastMessageInserted;
};

void NetCommandList::appendList(NetCommandList *list)
{
    if (list == 0)
        return;

    NetCommandRef *msg = list->m_first;
    while (msg != 0)
    {
        NetCommandRef *next = msg->m_next;
        NetCommandRef *temp = addMessage(msg->m_msg);
        if (temp != 0)
            temp->m_relay = msg->m_relay;
        msg = next;
    }
}
