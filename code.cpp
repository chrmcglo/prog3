#include <iostream>
#include <string>
class DobbeltlenketSirkularListe {
public:
    void leggtil(std::string Navn);
    void skrivUt();
    void slett(int id);
    void slett(std::string Navn);
    void skrivUtNavnAlfabetisk();
private:
    int next_id = 1;
    struct Node {
        int id;
        std::string Navn;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;
        Node(int id, std::string Navn) : id(id), Navn(Navn) {} 
    };
    std::shared_ptr<Node> head = nullptr;
    void insertSorted(std::shared_ptr<Node>& sorted, std::shared_ptr<Node> newNode);
};
void DobbeltlenketSirkularListe::leggtil(std::string Navn){
    int id = next_id++;
    std::shared_ptr<Node> newNode = std::make_shared<Node>(id, Navn);
    if (head == nullptr) {
        head = newNode;
        head->next = head;
        head->prev = head; 
    }
    else {
        std::shared_ptr<Node> tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
}
void DobbeltlenketSirkularListe::insertSorted(std::shared_ptr<Node>& sorted, std::shared_ptr<Node> newNode) {
    if (!sorted) {
        sorted = newNode;
        return;
    }
    if (newNode->Navn < sorted->Navn) {
        newNode->next = sorted;
        sorted->prev = newNode;
        sorted = newNode;
        return;
    }
    std::shared_ptr<Node> current = sorted;
    while (current->next != nullptr && current->next->Navn < newNode->Navn) {
        current = current->next;
    }
    newNode->next = current->next;
    if (current->next != nullptr) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}
void DobbeltlenketSirkularListe::skrivUtNavnAlfabetisk() {
    if (!head || head->next == head) {return;}
    std::shared_ptr<Node> tail = head->prev;
    tail->next = nullptr;
    head->prev = nullptr;
    std::shared_ptr<Node> sorted = nullptr;
    std::shared_ptr<Node> current = head;
    while (current != nullptr) {
        std::shared_ptr<Node> nextNode = current->next;
        current->next = nullptr;
        current->prev = nullptr;
        insertSorted(sorted, current);
        current = nextNode;
    }
    if (sorted != nullptr) {
        std::shared_ptr<Node> sortedTail = sorted;
        while (sortedTail->next != nullptr) {
            sortedTail = sortedTail->next;
        }
        sortedTail->next = sorted;
        sorted->prev = sortedTail;
        head = sorted;
    }
}
void DobbeltlenketSirkularListe::skrivUt(){
    if (!head) return;
    std::shared_ptr<Node> current = head;
    do {
        std::cout << "ID: " << current->id << ", Name: " << current->Navn << std::endl;
        current = current->next;
    } while (current != head);
}
void DobbeltlenketSirkularListe::slett(int a) {
    if (!head) return;
    std::shared_ptr<Node> current = head;
    do {
        if (current->id == a) {
            std::cout << "ID " << a << " Slettet" << std::endl;
            std::shared_ptr<Node> uPrev = current->prev;
            std::shared_ptr<Node> wNext = current->next;
            uPrev->next = wNext;
            wNext->prev = uPrev;
            if (current == head) {
                if (current->next == current) { 
                    head = nullptr;
                }
                else {
                    head = wNext;
                }
            }
            return;
        }
        current = current->next;
    } while (current != head);
}
void DobbeltlenketSirkularListe::slett(std::string a) {
    if (!head) return;
    std::shared_ptr<Node> current = head;
    std::shared_ptr<Node> start = head;
    bool firstIteration = true;
    while (head != nullptr) {
        if (current->Navn == a) {
            std::cout << "Navn " << a << " Slettet" << std::endl;
            std::shared_ptr<Node> uPrev = current->prev;
            std::shared_ptr<Node> wNext = current->next;
            uPrev->next = wNext;
            wNext->prev = uPrev;
            if (current == head) {
                if (current->next == current) { 
                    head = nullptr;
                    return;
                }
                else {
                    head = wNext;
                }
            }
            current = head;
            start = head;
            firstIteration = true;
        }
        else {
            current = current->next;

            if (current == start) {
                if (firstIteration) {
                    firstIteration = false;
                }
                else {
                    break;
                }
            }
        }
    }
}
int main() {
    DobbeltlenketSirkularListe liste;
    liste.leggtil("Julenissen");
    liste.leggtil("Silje");
    liste.leggtil("Jens");
    liste.leggtil("Jens");
    liste.leggtil("Maria");
    liste.leggtil("Christian");
    liste.leggtil("Sigrid");
    liste.leggtil("Jens");
    liste.leggtil("Emily");
    std::cout << "liste usortert, ID lavt til hoyt: " << std::endl;
    liste.skrivUt();
    liste.slett(1);
    liste.skrivUt();
    liste.slett(std::string("Jens"));
    liste.skrivUt();
    std::cout << "Sorterer listen alfabetisk  " << std::endl;
    liste.skrivUtNavnAlfabetisk();
    liste.skrivUt();
    return 0;
}
