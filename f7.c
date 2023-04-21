
void freq(int32_t fout, uint16_t i, uint16_t q){ // Set a CLK0,1,2 to fout Hz with phase i, q (on PLLA)
uint8_t rdiv = 0; // CLK pin sees fout/(2^rdiv)
if(fout > 300000000){ i/=3; q/=3; fout/=3; } // for higher freqs, use 3rd harmonic
if(fout < 500000){ rdiv = 7; fout = 128; } // Divide by 128 for fout 4..500kHz
uint16_t d; if(fout < 30000000) d = (16 * fxtal) / fout; else d = (32 * fxtal) / fout; // Integer part .. maybe 44?
if(fout < 3500000) d = (7 * fxtal) / fout; // PLL at 189MHz to cover 160m (freq>1.48MHz) when using 27MHz crystal
if(fout > 140000000) d = 4; // for f=140..300MHz; AN619; 4.1.3, this implies integer mode
if(d % 2) d++; // even numbers preferred for divider (AN619 p.4 and p.6)
if( (d * (fout - 5000) / fxtal) != (d * (fout + 5000) / fxtal) ) d += 2; // Test if multiplier remains same for freq deviation +/- 5kHz, if not use different divider to make same
uint32_t fvcoa = d * fout; // Variable PLLA VCO frequency at integer multiple of fout at around 27MHz16 = 432MHz
// si5351 spectral purity considerations: https://groups.io/g/QRPLabs/message/42662

  ms(MSNA, fvcoa, fxtal);                   // PLLA in fractional mode
  //ms(MSNB, fvcoa, fxtal);
  ms(MS0,  fvcoa, fout, PLLA, 0, i, rdiv);  // Multisynth stage with integer divider but in frac mode due to phase setting
  ms(MS1,  fvcoa, fout, PLLA, 0, q, rdiv);
#ifdef F_CLK2
freqb(F_CLK2);
#else
ms(MS2, fvcoa, fout, PLLA, 0, 0, rdiv);
#endif
if(iqmsa != (((int8_t)i-(int8_t)q)((int16_t)(fvcoa/fout))/90)){ iqmsa = ((int8_t)i-(int8_t)q)((int16_t)(fvcoa/fout))/90; reset(); }
oe(0b00000011); // output enable CLK0, CLK1

#ifdef x
ms(MSNA, fvcoa, fxtal);
ms(MSNB, fvcoa, fxtal);
#define F_DEV 4
ms(MS0, fvcoa, (fout + F_DEV), PLLA, 0, 0, rdiv);
ms(MS1, fvcoa, (fout + F_DEV), PLLA, 0, 0, rdiv);
ms(MS2, fvcoa, fout, PLLA, 0, 0, rdiv);
reset();
ms(MS0, fvcoa, fout, PLLA, 0, 0, rdiv);
delayMicroseconds(F_MCU/16000000 * 1000000UL/F_DEV); // Td = 1/(4 * Fdev) phase-shift https://tj-lab.org/2020/08/27/si5351%e5%8d%98%e4%bd%93%e3%81%a73mhz%e4%bb%a5%e4%b8%8b%e3%81%ae%e7%9b%b4%e4%ba%a4%e4%bf%a1%e5%8f%b7%e3%82%92%e5%87%ba%e5%8a%9b%e3%81%99%e3%82%8b/
ms(MS1, fvcoa, fout, PLLA, 0, 0, rdiv);
oe(0b00000011); // output enable CLK0, CLK1
#endif
_fout = fout; // cache
_div = d;
_msa128min512 = fvcoa / fxtal * 128 - 512;
_msb128=((uint64_t)(fvcoa % fxtal)_MSC128) / fxtal;
//_mod = fvcoa % fxtal;
}