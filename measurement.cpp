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
#include "measurement.h"

MSS::MSS(double val, double stat, double syst)
{
  setVal(val);
  setStat(stat);
  setSyst(syst);
}

MSS MSS::operator+ (const MSS& b) {
  return add(*this, b);
}

MSS MSS::operator* (const MSS& b) {
  return mul(*this, b);
}

MSS MSS::operator- (const MSS& b) {
  return sub(*this, b);
}

MSS MSS::operator/ (const MSS& b) {
  return div(*this, b);
}

MSS& MSS::operator+= (const MSS& b) {
  (*this) = (*this) + b;
  return *this;
}

MSS& MSS::operator*= (const MSS& b) {
  (*this) = (*this) * b;
  return *this;
}

MSS& MSS::operator-= (const MSS& b) {
  (*this) = (*this) - b;
  return *this;
}

MSS& MSS::operator/= (const MSS& b) {
  (*this) = (*this) / b;
  return *this;
}


MSS MSS::add (const MSS& a, const MSS& b, double cStat, double cSyst) {
  double val  = a.m_val + b.m_val;
  double stat = sqrt(a.m_stat*a.m_stat  +  b.m_stat*b.m_stat + 2*a.m_stat*b.m_stat*cStat);
  double syst = sqrt(a.m_syst*a.m_syst  +  b.m_syst*b.m_syst + 2*a.m_syst*b.m_syst*cSyst);
  return MSS(val, stat, syst);
}

MSS MSS::mul (const MSS& a, const MSS& b, double cStat, double cSyst) {
  double val  = a.m_val * b.m_val;
  double stat = val*sqrt(a.m_stat*a.m_stat/(a.m_val*a.m_val) + (b.m_stat*b.m_stat)/(b.m_val*b.m_val) + 2*a.m_stat*b.m_stat*cStat/(a.m_val*b.m_val));
  double syst = val*sqrt(a.m_syst*a.m_syst/(a.m_val*a.m_val) + (b.m_syst*b.m_syst)/(b.m_val*b.m_val) + 2*a.m_syst*b.m_syst*cSyst/(a.m_val*b.m_val));
  return MSS(val, stat, syst);
}

MSS MSS::sub (const MSS& a, const MSS& b, double cStat, double cSyst) {
  double val  = a.m_val - b.m_val;
  double stat = sqrt(a.m_stat*a.m_stat  +  b.m_stat*b.m_stat - 2*a.m_stat*b.m_stat*cStat);
  double syst = sqrt(a.m_syst*a.m_syst  +  b.m_syst*b.m_syst - 2*a.m_syst*b.m_syst*cSyst);
  return MSS(val, stat, syst);
}

MSS MSS::div (const MSS& a, const MSS& b, double cStat, double cSyst) {
  double val  = a.m_val / b.m_val;
  double stat = val*sqrt(a.m_stat*a.m_stat/(a.m_val*a.m_val) + (b.m_stat*b.m_stat)/(b.m_val*b.m_val) - 2*a.m_stat*b.m_stat*cStat/(a.m_val*b.m_val));
  double syst = val*sqrt(a.m_syst*a.m_syst/(a.m_val*a.m_val) + (b.m_syst*b.m_syst)/(b.m_val*b.m_val) - 2*a.m_syst*b.m_syst*cSyst/(a.m_val*b.m_val));
  return MSS(val, stat, syst);
}


double MSS::getTotalUncertainty() {
  return sqrt(m_stat*m_stat+m_syst*m_syst);
}

std::string MSS::getString(const std::string& delimiter, int digits) {
  std::stringstream fmt;
  fmt << std::setprecision(digits) << std::fixed << m_val;
  fmt << " " << delimiter << " " << m_stat;
  fmt << " " << delimiter << " " << m_syst;
  return fmt.str();
}

std::string MSS::getStringSqSum(const std::string& delimiter, int digits) {
  std::stringstream fmt;
  fmt << std::setprecision(digits) << std::fixed << m_val;
  fmt << " " << delimiter << " " << getTotalUncertainty();
  return fmt.str();
}


