
class ConnectionManager{
public:
    virtual void dial(string);
    virtual void hangup();
};

class IConnectionManager : public ConnectionManager{
public:
    void dial(string phoneNumber);
    void hangup();
    
};


class DataTransfer{
public:
    virtual void DataTransfer(IConnectionManager);
};


class IDataTransfer : public DataTransfer{
public:
    void DataTransfer(IConnectionManager cm);
};


class Phone : public ConnectionManager, public DataTransfer{
};




