/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2001
 *
 *  Last modified:
 *     $Date: 2016-04-19 17:19:45 +0200 (Tue, 19 Apr 2016) $ by $Author: schulte $
 *     $Revision: 14967 $
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

#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>

using namespace Gecode;
using namespace std;

/**
 * \brief %Example: %Grocery puzzle
 *
 * A kid goes into a grocery store and buys four items. The cashier
 * charges $7.11, the kid pays and is about to leave when the cashier
 * calls the kid back, and says ''Hold on, I multiplied the four items
 * instead of adding them; I'll try again; Hah, with adding them the
 * price still comes to $7.11''. What were the prices of the four items?
 *
 * The model is taken from: Christian Schulte, Gert Smolka, Finite Domain
 * Constraint Programming in Oz. A Tutorial. 2001.
 * Available from: http://www.mozart-oz.org/documentation/fdt/
 *
 * \ingroup Example
 *
 */
class Grocery : public Space {
protected:
  /// The price of each item
  IntVarArray abcd;
  /// Sum and product of prices
  static const int s = 711;
  /// Decimal product of prices
  static const int p = 711 * 100 * 100 * 100;
public:
  /// The actual model
  Grocery():  abcd(*this,4,0,s) {
    IntVar a(abcd[0]), b(abcd[1]), c(abcd[2]), d(abcd[3]);

    // The sum of all variables is s
    rel(*this, a+b+c+d == s);

    // The product of all variables is s (corrected by scale factor)
    IntVar t1(*this,1,p);
    IntVar t2(*this,1,p);
    IntVar t3(*this,p,p);

    mult(*this, a, b, t1);
    mult(*this, c, d, t2);
    mult(*this, t1, t2, t3);

    // Break symmetries: order the variables
    rel(*this, abcd, IRT_LQ);  // TRY COMENTING THIS LINE

    branch(*this, abcd, INT_VAR_NONE(), INT_VAL_SPLIT_MAX());
  }

  /// Constructor for cloning \a s
  Grocery(bool share, Grocery& s) : Space(share,s) {
    abcd.update(*this, share, s.abcd);
  }

  /// Copy during cloning
  virtual Space* copy(bool share) {
    return new Grocery(share,*this);
  }

  /// Print solution
  void print(void) {
    cout << "\t" << abcd << endl;
  }
};

/** \brief Main-function
 *  \relates Grocery
 */
int main(int argc, char* argv[]) {
  Grocery* m = new Grocery();
  DFS<Grocery> e(m);
  delete m;
  while (Grocery* s = e.next()) {
    s->print(); delete s;
  }
  return 0;
}

// STATISTICS: example-any

