/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2001
 *
 *  Last modified:
 *     $Date: 2015-09-11 16:29:45 +0200 (Fri, 11 Sep 2015) $ by $Author: schulte $
 *     $Revision: 14672 $
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
 * \brief %Example: Magic squares
 *
 * Compute magic squares of arbitrary size
 *
 * See problem 19 at http://www.csplib.org/.
 *
 * \ingroup Example
 *
 */
class MagicSquare : public Space {
private:
  /// Size of magic square
  const int n=3;
  /// Fields of square
  IntVarArray x;

public:
  /// Post constraints
  MagicSquare(): x(*this,n*n,1,n*n) {
    // Number of fields on square
    const int nn = n*n;

    // Sum of all a row, column, or diagonal
    const int s  = nn*(nn+1) / (2*n);

    // Matrix-wrapper for the square
    Matrix<IntVarArray> m(x, n, n);

    for (int i = n; i--; ) {
      linear(*this, m.row(i), IRT_EQ, s);
      linear(*this, m.col(i), IRT_EQ, s);
    }
    // Both diagonals must have sum s
    {
      IntVarArgs d1y(n);
      IntVarArgs d2y(n);
      for (int i = n; i--; ) {
        d1y[i] = m(i,i);
        d2y[i] = m(n-i-1,i);
      }
      linear(*this, d1y, IRT_EQ, s);
      linear(*this, d2y, IRT_EQ, s);
    }

    // All fields must be distinct
    distinct(*this, x);

    // Break some  symmetries
    // TO-DO
  
    branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_SPLIT_MIN());

  }

  /// Constructor for cloning \a s
  MagicSquare(bool share, MagicSquare& s) : Space(share,s), n(s.n) {
    x.update(*this, share, s.x);
  }

  /// Copy during cloning
  virtual Space*
  copy(bool share) {
    return new MagicSquare(share,*this);
  }
  /// Print solution
  virtual void print(ostream& os) const {
    // Matrix-wrapper for the square
    Matrix<IntVarArray> m(x, n, n);
    for (int i = 0; i<n; i++) {
      os << "\t";
      for (int j = 0; j<n; j++) {
        os.width(2);
        os << m(i,j) << "  ";
      }
      os << endl;
    }
    os << endl;
  }

};

/** \brief Main-function
 *  \relates MagicSquare
 */
int main(int argc, char* argv[]) {
  MagicSquare* m = new MagicSquare();
  DFS<MagicSquare> e(m);
  delete m;
  while (MagicSquare* s = e.next()) {
    s->print(cout); delete s;
  }
  return 0;
}

// STATISTICS: example-any

