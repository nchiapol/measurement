/** MSS -- measurement with statistical and systematic uncertainties (cf. 12.1.1 in thesis)
 *
 *  Copyright 2016, Nicola Chiapolini, nicola.chiapolini@physik.uzh.ch
 *
 *  License: GNU General Public License version 3,
 *           or (at your option) any later version.
 *
 *  This program is distributed WITHOUT ANY WARRANTY.
 *  See the GNU General Public License for more details.
 *
 */
#ifndef MSS_H
#define MSS_H

#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

class MSS
{
  public:
    MSS () {};
    MSS(double val, double stat = 0 , double syst = 0);
    ~MSS() {};
    double val() { return m_val; }
    double stat() { return m_stat; }
    double syst() { return m_syst; }
    void setSyst(double syst) { m_syst = syst; }
    void setStat(double stat) { m_stat = stat; }
    void setVal(double val) { m_val = val; }
    double getTotalUncertainty();
    std::string getString(const std::string& delimiter = "+/-", int digits = 5);
    std::string getStringSqSum(const std::string& delimiter = "+/-", int digits = 5);

    MSS operator + (const MSS& b);
    MSS operator * (const MSS& b);
    MSS operator - (const MSS& b);
    MSS operator / (const MSS& b);
    static MSS add (const MSS& a, const MSS& b, double cStat = 0, double cSyst = 0);
    static MSS mul (const MSS& a, const MSS& b, double cStat = 0, double cSyst = 0);
    static MSS sub (const MSS& a, const MSS& b, double cStat = 0, double cSyst = 0);
    static MSS div (const MSS& a, const MSS& b, double cStat = 0, double cSyst = 0);
    MSS& operator += (const MSS& b);
    MSS& operator *= (const MSS& b);
    MSS& operator -= (const MSS& b);
    MSS& operator /= (const MSS& b);
  protected:
    double m_val;
    double m_stat;
    double m_syst;
  private:

};

#endif // MSS_H
