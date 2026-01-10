#include <iostream>
#include <stdexcept>

class Stack
{
private:
    int *tab;
    int size;
    int nb;

public:
    Stack(int s) : nb(0)
    {
        size = s;
        tab = new int[size];
    }
    ~Stack()
    {
        delete[] tab;
    }

    Stack(const Stack &tbl)
    {
        size = tbl.size;
        nb = tbl.nb;
        tab = new int[size];
        for (int i = 0; i < nb; i++)
        {
            tab[i] = tbl.tab[i];
        }
    }

    Stack &operator=(const Stack &tbl)
    {
        if (this == &tbl) // this est un pointeur qui pointe sur l'objet courant qui est une référence
        {
            return *this;
        }
        nb = tbl.nb;
        size = tbl.size;
        delete[] tab;
        tab = new int[size];
        for (int i = 0; i < nb; i++)
        {
            tab[i] = tbl.tab[i];
        }
        return *this; // retourne l'objet courant
    }

    bool is_full()
    {
        return nb >= size;
    }

    void push(int value)
    {
        if (is_full())
        {
            throw std::overflow_error("pile pleine ");
        }
        else
        {
            tab[nb] = value;
            nb += 1;
        }
    }
};

int main()
{
    // test de l'opérateur d'affectation
    {

        Stack st(10);
        {
            Stack st2(5);
            st2.push(3);
            st = st2; // appel de l'opérateur d'affectation
        }
        st.push(17); // il suffit de supprimer la méthode operator= pour voir qu'on a deux free error
    }
    // test du constructeur de copie
    {
        Stack st(10);
        {
            Stack st2 = st; // appel du constructeur de copie
        }
        st.push(42); // il suffit de supprimer le constructeur de copie pour voir qu'on a une aborted(core dumped) error
    }

    return 0;
}
