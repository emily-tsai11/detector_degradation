#ifndef SMALL_TEXT
#define SMALL_TEXT


void MySmallText(Double_t x, Double_t y, Color_t color, std::string text) {

  Double_t tsize = 0.044;
  TLatex l;
  l.SetTextSize(tsize);
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x, y, text.c_str());
}


#endif
