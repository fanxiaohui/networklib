# Single Responsibility Principle

Single Responsibility Principle ,中文含义是 单一职责原则。

## 定义

There should never be more than one reason for a class to change.

## 单一职责原则的优点

* 类的复杂性降低
* 可读性提高
* 可维护性提高
* 变更引起的风险降低

注：单一职责原则提出了一个编写程序的标准，用“职责”或“变化原因”衡量接口或类设计得是否优良，但这些都是不可度量的，所以，我们需要因项目而异，因环境而异


# 单一职责原则同样适用于方法

即一个方法尽可能做一件事。

# 对于单一职责原因

接口一定要做到单一职责，类的设计尽量做到只有一个原因引起变化。


# 程序

````
class IPhone{
public:
    void chat(object);
    void dial(stringPhoneNumber);
    void hangup();
};

````

电话类：注：dial：拨通电话；chat：通话；hangup：挂电话

这么一个接口包含两个职责：协议管理（dial，hangup）和数据传送（chat）

这样看来，协议接通会引起这个接口或类的变化，数据传送也会引起这个接口或类的变化。

两个原因都引起了类的变化。但是！！这两个职责并不互相影响。所以说：拆分！！！


````
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


class Phone{
    ConnectionManager con;
    DataTransfer date;
};

````

这么做，我们就实现了单一职责。
但是这样会导致一个问题：该方式需要把ConnectionManager和DataTransfer组合在一起才能使用，组合是一种强耦合关系拥有共同生命期，而且增加了类的复杂性，多了两个类，不好不好。

修改后如下
````
class Phone : public IConnectionManager, public IDataTransfer{
};
````




