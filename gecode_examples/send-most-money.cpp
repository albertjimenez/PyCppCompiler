/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2001
 *
 *  Last modified:
 *     $Date: 2017-03-17 23:04:57 +0100 (Fri, 17 Mar 2017) $ by $Author: schulte $
 *     $Revision: 15597 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#include <gecode/int.hh>
#include <gecode/search.hh>
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
class SendMostMoney : public Space {
protected:
  /// Number of letters
  static const int nl = 8;
  /// Array of letters
  IntVarArray le;
public:
  
  /// Actual model
  SendMostMoney() : le(*this,nl,0,9) {
    IntVar s(le[0]), e(le[1]), n(le[2]), d(le[3]), m(le[4]), o(le[5]), r(le[6]), y(le[7]);

    rel(*this, s, IRT_NQ, 0);
    rel(*this, m, IRT_NQ, 0);

    distinct(*this, le);

    rel(*this,            1000*s+100*e+10*n+d
                  +         1000*m+100*o+10*r+e
                 == 10000*m+1000*o+100*n+10*e+y);         

    branch(*this, le, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  /// Print solution
  void print(void) {
   IntVar e(le[1]), n(le[2]), m(le[4]), o(le[5]), y(le[7]);
   int best_obj= 10000*m.val()+1000*o.val()+100*n.val()+10*e.val()+y.val();
   cout << le << " o.f=" << best_obj << endl;
  
  }

  /// Constructor for cloning \a s
  SendMostMoney(bool share, SendMostMoney& s) : Space(share,s) {
    le.update(*this, share, s.le);
  }
  /// Copy during cloning
  virtual Space* copy(bool share) {
    return new SendMostMoney(share,*this);
  }

  virtual void constrain(const Space& _b) {
    const SendMostMoney& b = static_cast<const SendMostMoney&>(_b);

    IntVar e(le[1]), n(le[2]), m(le[4]), o(le[5]), y(le[7]);

    IntVar b_e(b.le[1]), b_n(b.le[2]), b_m(b.le[4]), 
           b_o(b.le[5]), b_y(b.le[7]);

    int money = (10000*b_m.val()+1000*b_o.val()+100*b_n.val()+
                 10*b_e.val()+b_y.val());

    rel(*this, 10000*m+1000*o+100*n+10*e+y > money);
  }

};

/** \brief Main-function
 *  \relates SendMostMoneyMoney
 */
int main(int argc, char* argv[]) {
  SendMostMoney* m = new SendMostMoney();
  BAB<SendMostMoney> e(m);
  delete m;
  while (SendMostMoney* s = e.next()) {
    s->print(); delete s;
  }
  return 0;
}



