
struct MenuParameter {
   String textBefore;
   unsigned int &value;
   String (&valueFormatter)(unsigned int value);
   String textAfter;
};

struct Menu {
   String text;
   unsigned char parametersCount;
   MenuParameter *pParameters;
};


