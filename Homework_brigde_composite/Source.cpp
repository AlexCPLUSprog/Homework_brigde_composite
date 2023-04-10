#include <iostream>
#include <vector>


class ITransport {
public:
    virtual void load_cargo() = 0;
};

class Autotrack : public ITransport {
public:
    void load_cargo() override {
        std::cout << "��������� �������� ����� �������� �����������\n";
    }
};

class Car : public ITransport {
public:
    void load_cargo() override {
        std::cout << "��������� ������� ����� ������� �����������\n";
    }
};


class GasolineTankerTrack : public ITransport {
public:
    void load_cargo() override {
        std::cout << "��������� ����� ����������\n";
    }
};


class IStorage {
public:
    IStorage(ITransport* transport) : _transport(transport) {}
    virtual void receive_cargo() = 0;
    virtual void store_cargo() = 0;
protected:
    ITransport* _transport;
};

class Warehouse : public IStorage {
public:
    Warehouse(ITransport* transport) : IStorage(transport) {}
    void receive_cargo() override {
        _transport->load_cargo();
    }
    void store_cargo() override {
        std::cout << "�������� �������� ����� �� ������\n";
    }
};

class Garage : public IStorage {
public:
    Garage(ITransport* transport) : IStorage(transport) {}
    void receive_cargo() override {
        _transport->load_cargo();
    }
    void store_cargo() override {
        std::cout << "�������� ������� ����� � ������\n";
    }
};

class StorageTank : public IStorage {
public:
    StorageTank(ITransport* transport) : IStorage(transport) {}
    void receive_cargo() override {
        _transport->load_cargo();
    }
    void store_cargo() override {
        std::cout << "�������� ����� �� ���������\n";
    }
};


class StorageComposite : public IStorage {
public:
    StorageComposite(ITransport* transport) : IStorage(transport) {}
    void add(IStorage* storage) {
        _storages.push_back(storage);
    }
    void receive_cargo() override {
        for (IStorage* storage : _storages) {
            storage->receive_cargo();
        }
    }
    void store_cargo() override {
        for (IStorage* storage : _storages) {
            storage->store_cargo();
        }
    }
private:
    std::vector<IStorage*> _storages;
};



int main() {
    setlocale(0, "ru");
    int n = 10;
    ITransport* truck = new Autotrack();
    ITransport* car = new Car();
    ITransport* tanker = new GasolineTankerTrack();
    IStorage* warehouse = new Warehouse(truck);
    IStorage* garage = new Garage(car);
    IStorage* storagetank = new StorageTank(tanker);
    StorageComposite* composite = new StorageComposite(truck);
    do {
        std::cout << "�������� ��� �����:\n";
        std::cout << "1 - �������\n";
        std::cout << "2 - ������\n";
        std::cout << "3 - �����\n";
        std::cout << "0 - ����� --> ";
      
        std::cin >> n;
        switch (n) {
        case 1:
            composite->add(warehouse);
            composite->receive_cargo();
            composite->store_cargo();
            break;
        case 2:
            composite->add(garage);
            composite->receive_cargo();
            composite->store_cargo();
            break;
        case 3:
            composite->add(storagetank);
            composite->receive_cargo();
            composite->store_cargo();
            break;
        case 0:
            std::cout << "��������� ���������\n";           
            break;
        default:
            std::cout << "������������ ��������. ������� ��� ���\n";
            break;
        }
        
    } while (n != 0);

    return 0;
}
