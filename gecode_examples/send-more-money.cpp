/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */


#include <gecode/int.hh>
#include <gecode/minimodel.hh>

using namespace Gecode;
using namespace std;


/**
 * \brief %Example: SEND+MORE=MONEY puzzle
 *
 * Well-known cryptoarithmetic puzzle.
 * Henry Dudeney, Strand Magazine, July 1924.
 *
 * \ingroup Example
 *
 */
class SendMoreMoney : public Space {
protected:
    /// Number of letters
    static const int nl = 8;
    /// Array of letters
    IntVarArray le;
public:

    /// Actual model
    SendMoreMoney() : le(*this, nl, 0, 9) {
        IntVar s(le[0]), e(le[1]), n(le[2]), d(le[3]), m(le[4]), o(le[5]), r(le[6]), y(le[7]);

        rel(*this, s, IRT_NQ, 0);
        rel(*this, m, IRT_NQ, 0);

        distinct(*this, le);

        rel(*this, 1000 * s + 100 * e + 10 * n + d
                   + 1000 * m + 100 * o + 10 * r + e
                   == 10000 * m + 1000 * o + 100 * n + 10 * e + y);

        branch(*this, le, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }

    /// Print solution
    void print(void) {
        cout << "\t" << le << endl;
    }

    /// Constructor for cloning \a s
    SendMoreMoney(bool share, SendMoreMoney &s) : Space(share, s) {
        le.update(*this, share, s.le);
    }

    /// Copy during cloning
    virtual Space *copy(bool share) {
        return new SendMoreMoney(share, *this);
    }
};

/** \brief Main-function
 *  \relates SendMoreMoneyMoney
 */
int main(int argc, char *argv[]) {
    auto *m = new SendMoreMoney();
    DFS<SendMoreMoney> e(m);
    delete m;
    while (SendMoreMoney *s = e.next()) {
        s->print();
        delete s;
    }
    return 0;
}



