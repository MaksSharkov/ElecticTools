//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "fstream.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString pathAS;
char* path;
const int Ma = 30;
char per1[Ma];
ofstream outfile;
ifstream infile;

//------------------------Электроинструменты---------------------------------
class ElectricTools
{
        protected:
                AnsiString name;     //Название
                AnsiString country;  //Страна производитель
                int voltage;         //Рабочее напряжение
                int power;           //Мощность
                int weight;          //Вес
                int guarantee;       //Гарантия

        public:
                ElectricTools(){}    //Конструктор по умолчанию
                ElectricTools(AnsiString NM, AnsiString CN, int VL,
                int PW, int WG, int GR) //Конструктор инициализации
              : name(NM),
                country(CN),
                voltage(VL),
                power(PW),
                weight(WG),
                guarantee(GR)
                {}
                void operator = (const ElectricTools&);  //Присваивание
                bool operator == (const ElectricTools&); //Равно
                bool operator != (const ElectricTools&); //Не равно
                virtual void print(TMemo*)=0;           //Вывод
                virtual void Get_vals(AnsiString*)=0;   //Возврат значений полей класса
                virtual void Write_to_file() = 0;       //Запись в файл
                virtual void Read_from_file() = 0;      //Чтение из файла
                ~ElectricTools(){}  //Деструктор
};

//---------------------------------------------------------------------------
class Tools  : public ElectricTools
{
  protected:

  public:
    Tools(){}
    Tools(AnsiString NM, AnsiString CN, int VL, int PW, int WG, int GR)
     :ElectricTools(NM, CN, VL, PW, WG, GR)
    {}
    void print(TMemo* Memo)
    {
      Memo->Lines->Add("Название                             "+name);
      Memo->Lines->Add("Страна производитель                 "+country);
      Memo->Lines->Add("Рабочее напряжение                   "+IntToStr(voltage)+" Вольт");
      Memo->Lines->Add("Мощность                             "+IntToStr(power)+" Ватт");
      Memo->Lines->Add("Вес                                  "+IntToStr(weight)+" грамм");
      Memo->Lines->Add("Гарантия                             "+IntToStr(guarantee)+" мес.");
    }
        void Get_vals(AnsiString* ptrd)
          {}
    ~Tools(){}
};

//----------------------Шуруповерты------------------------------------------
class Screwdrivers : public Tools
{
        protected:
                int battery;  //Емкость батареи
                int torque;          //MAX крутящий момент
                int speed;           //Кол-во скоростей
                AnsiString hit;      //Наличие удара

        public:
                Screwdrivers(){}
                Screwdrivers(AnsiString NM, AnsiString CN, int VL,
                int PW, int WG, int GR, int BT, int TR, int SP, AnsiString HT)
                :Tools(NM, CN, VL, PW, WG, GR),
                battery(BT),
                torque(TR),
                speed(SP),
                hit(HT)
                {}
        Screwdrivers(const Screwdrivers& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         battery = obj.battery;
         torque = obj.torque;
         speed = obj.speed;
         hit = obj.hit;

        }
        void operator = (const Screwdrivers& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         battery = obj.battery;
         torque = obj.torque;
         speed = obj.speed;
         hit = obj.hit;
        }
        bool operator == (const Screwdrivers& obj)
        {
         if(
         (name == obj.name)&&
         (country == obj.country)&&
         (voltage == obj.voltage)&&
         (power == obj.power)&&
         (weight == obj.weight)&&
         (guarantee == obj.guarantee)&&
         (battery == obj.battery)&&
         (torque == obj.torque)&&
         (speed == obj.speed)&&
         (hit == obj.hit))
          return true;
          else return false;
        }

        bool operator != (const Screwdrivers& obj)
        {if(*(this)==obj) return false; else return true;};

    void print(TMemo* Memo)
    {
      Memo->Lines->Add("------------------Шуруповерт----------------------");
      Tools::print(Memo);
      Memo->Lines->Add("Емкость батареи                      "+IntToStr(battery)+" mAh");
      Memo->Lines->Add("MAX крутящий момент                  "+IntToStr(torque)+" Нм");
      Memo->Lines->Add("Кол-во скоростей                     "+IntToStr(speed));
      Memo->Lines->Add("Наличие удара                        "+hit);
      Memo->Lines->Add("++++++++++++++++++++++++++++++++++++++++++++++++++");
      Memo->Lines->Add("");
      Memo->Lines->Add("");
    }
        void Get_vals(AnsiString* ptrd)
             {
              ptrd[0] = name;
              ptrd[1] = country;
              ptrd[2] = IntToStr(voltage);
              ptrd[3] = IntToStr(power);
              ptrd[4] = IntToStr(weight);
              ptrd[5] = IntToStr(guarantee);
              ptrd[6] = IntToStr(battery);
              ptrd[7] = IntToStr(torque);
              ptrd[8] = IntToStr(speed);
              ptrd[9] = hit;
             }
        void Write_to_file()
             {
              outfile
              <<name.c_str()<<endl
              <<country.c_str()<<endl
              <<voltage<<endl
              <<power<<endl
              <<weight<<endl
              <<guarantee<<endl
              <<battery<<endl
              <<torque<<endl
              <<speed<<endl
              <<hit.c_str()<<endl;
             }

        void Read_from_file()
             {
              infile.getline(per1,Ma);
              name = per1;
              infile.getline(per1,Ma);
              country = per1;
              infile.getline(per1,Ma);
              voltage = StrToInt(per1);
              infile.getline(per1,Ma);
              power = StrToInt(per1);
              infile.getline(per1,Ma);
              weight = StrToInt(per1);
              infile.getline(per1,Ma);
              guarantee = StrToInt(per1);
              infile.getline(per1,Ma);
              battery = StrToInt(per1);
              infile.getline(per1,Ma);
              torque = StrToInt(per1);
              infile.getline(per1,Ma);
              speed = StrToInt(per1);
              infile.getline(per1,Ma);
              hit = per1;
             }
                ~Screwdrivers(){}
};

//-------------------------Клеевые пистолеты---------------------------------
class GlueGuns : public Tools
{
        protected:
                AnsiString performance;   //Производительность
                int time;                 //Время нагрева
                int diameter;             //Диаметр стержня
                int temperature;          //Температура нагрева

        public:
                GlueGuns(){}
                GlueGuns(AnsiString NM, AnsiString CN, int VL,
                int PW, int WG, int GR, AnsiString PR, int TM, int DM, int TMP)
                :Tools(NM, CN, VL, PW, WG, GR),
                performance(PR),
                time(TM),
                diameter(DM),
                temperature(TMP)
                {}
        GlueGuns(const GlueGuns& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         performance = obj.performance;
         time = obj.time;
         diameter = obj.diameter;
         temperature = obj.temperature;

        }
        void operator = (const GlueGuns& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         performance = obj.performance;
         time = obj.time;
         diameter = obj.diameter;
         temperature = obj.temperature;
        }
        bool operator == (const GlueGuns& obj)
        {
         if(
         (name == obj.name)&&
         (country == obj.country)&&
         (voltage == obj.voltage)&&
         (power == obj.power)&&
         (weight == obj.weight)&&
         (guarantee == obj.guarantee)&&
         (performance == obj.performance)&&
         (time == obj.time)&&
         (diameter == obj.diameter)&&
         (temperature == obj.temperature))
          return true;
          else return false;
        }

        bool operator != (const GlueGuns& obj)
        {if(*(this)==obj) return false; else return true;};

    void print(TMemo* Memo)
    {
      Memo->Lines->Add("---------------Клеевой пистолет-------------------");
      Tools::print(Memo);
      Memo->Lines->Add("Производительность                   "+performance+" грамм/мин");
      Memo->Lines->Add("Время нагрева                        "+IntToStr(time)+" сек");
      Memo->Lines->Add("Диаметр стержня                      "+IntToStr(diameter)+" мм");
      Memo->Lines->Add("Рабочая температура                  "+IntToStr(temperature)+" C`");
      Memo->Lines->Add("++++++++++++++++++++++++++++++++++++++++++++++++++");
      Memo->Lines->Add("");
      Memo->Lines->Add("");
    }
        void Get_vals(AnsiString* ptrd)
             {
              ptrd[0] = name;
              ptrd[1] = country;
              ptrd[2] = IntToStr(voltage);
              ptrd[3] = IntToStr(power);
              ptrd[4] = IntToStr(weight);
              ptrd[5] = IntToStr(guarantee);
              ptrd[6] = performance;
              ptrd[7] = IntToStr(time);
              ptrd[8] = IntToStr(diameter);
              ptrd[9] = IntToStr(temperature);
             }
        void Write_to_file()
             {
              outfile
              <<name.c_str()<<endl
              <<country.c_str()<<endl
              <<voltage<<endl
              <<power<<endl
              <<weight<<endl
              <<guarantee<<endl
              <<performance.c_str()<<endl
              <<time<<endl
              <<diameter<<endl
              <<temperature<<endl;
             }

        void Read_from_file()
             {
              infile.getline(per1,Ma);
              name = per1;
              infile.getline(per1,Ma);
              country = per1;
              infile.getline(per1,Ma);
              voltage = StrToInt(per1);
              infile.getline(per1,Ma);
              power = StrToInt(per1);
              infile.getline(per1,Ma);
              weight = StrToInt(per1);
              infile.getline(per1,Ma);
              guarantee = StrToInt(per1);
              infile.getline(per1,Ma);
              performance = per1;
              infile.getline(per1,Ma);
              time = StrToInt(per1);
              infile.getline(per1,Ma);
              diameter = StrToInt(per1);
              infile.getline(per1,Ma);
              temperature = StrToInt(per1);
             }
                ~GlueGuns(){}
};

//--------------------------Электропилы--------------------------------------
class ElectricSaw : public Tools
{
        protected:
                int length;         //Длина шины
                int step;           //Шаг цепи
                AnsiString start;   //Плавный старт
        public:
                ElectricSaw(){}
                ElectricSaw(AnsiString NM, AnsiString CN, int VL,
                int PW, int WG, int GR, int LN, int ST, AnsiString STR)
                :Tools(NM, CN, VL, PW, WG, GR),
                length(LN),
                step(ST),
                start(STR)
                {}

        ElectricSaw(const ElectricSaw& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         length = obj.length;
         step = obj.step;
         start = obj.start;

        }
        void operator = (const ElectricSaw& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         length = obj.length;
         step = obj.step;
         start = obj.start;

        }
        bool operator == (const ElectricSaw& obj)
        {
         if(
         (name == obj.name)&&
         (country == obj.country)&&
         (voltage == obj.voltage)&&
         (power == obj.power)&&
         (weight == obj.weight)&&
         (guarantee == obj.guarantee)&&
         (length == obj.length)&&
         (step == obj.step)&&
         (start == obj.start))
          return true;
          else return false;
        }

        bool operator != (const ElectricSaw& obj)
        {if(*(this)==obj) return false; else return true;};

    void print(TMemo* Memo)
    {
      Memo->Lines->Add("------------------Электропила---------------------");
      Tools::print(Memo);
      Memo->Lines->Add("Длина шины                           "+IntToStr(length)+" ''");
      Memo->Lines->Add("Шаг цепи                             "+IntToStr(step)+" ''");
      Memo->Lines->Add("Плавный старт                        "+start);
      Memo->Lines->Add("++++++++++++++++++++++++++++++++++++++++++++++++++");
      Memo->Lines->Add("");
      Memo->Lines->Add("");
    }
        void Get_vals(AnsiString* ptrd)
             {
              ptrd[0] = name;
              ptrd[1] = country;
              ptrd[2] = IntToStr(voltage);
              ptrd[3] = IntToStr(power);
              ptrd[4] = IntToStr(weight);
              ptrd[5] = IntToStr(guarantee);
              ptrd[6] = IntToStr(length);
              ptrd[7] = IntToStr(step);
              ptrd[8] = start;
             }
        void Write_to_file()
             {
              outfile
              <<name.c_str()<<endl
              <<country.c_str()<<endl
              <<voltage<<endl
              <<power<<endl
              <<weight<<endl
              <<guarantee<<endl
              <<length<<endl
              <<step<<endl
              <<start.c_str()<<endl;
             }

        void Read_from_file()
             {
              infile.getline(per1,Ma);
              name = per1;
              infile.getline(per1,Ma);
              country = per1;
              infile.getline(per1,Ma);
              voltage = StrToInt(per1);
              infile.getline(per1,Ma);
              power = StrToInt(per1);
              infile.getline(per1,Ma);
              weight = StrToInt(per1);
              infile.getline(per1,Ma);
              guarantee = StrToInt(per1);
              infile.getline(per1,Ma);
              length = StrToInt(per1);
              infile.getline(per1,Ma);
              step = StrToInt(per1);
              infile.getline(per1,Ma);
              start = per1;
             }
                ~ElectricSaw(){}
};

//------------------------Отбойные молотки-----------------------------------
class Jackhammers : public Tools
{
        protected:
                int force;           //Сила удара
                AnsiString type;     //Тип патрона
                int count;           //Ударов/мин
        public:
                Jackhammers(){}
                Jackhammers(AnsiString NM, AnsiString CN, int VL,
                int PW, int WG, int GR, int FR, AnsiString TP, int CNT)
                :Tools(NM, CN, VL, PW, WG, GR),
                force(FR),
                type(TP),
                count(CNT)
                {}

        Jackhammers(const Jackhammers& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         force = obj.force;
         type = obj.type;
         count = obj.count;

        }
        void operator = (const Jackhammers& obj)
        {
         name = obj.name;
         country = obj.country;
         voltage = obj.voltage;
         power = obj.power;
         weight = obj.weight;
         guarantee = obj.guarantee;
         force = obj.force;
         type = obj.type;
         count = obj.count;

        }
        bool operator == (const Jackhammers& obj)
        {
         if(
         (name == obj.name)&&
         (country == obj.country)&&
         (voltage == obj.voltage)&&
         (power == obj.power)&&
         (weight == obj.weight)&&
         (guarantee == obj.guarantee)&&
         (force == obj.force)&&
         (type == obj.type)&&
         (count == obj.count))
          return true;
          else return false;
        }

        bool operator != (const Jackhammers& obj)
        {if(*(this)==obj) return false; else return true;};

    void print(TMemo* Memo)
    {
      Memo->Lines->Add("----------------Отбойный молоток------------------");
      Tools::print(Memo);
      Memo->Lines->Add("Сила удара                           "+IntToStr(force)+" Дж");
      Memo->Lines->Add("Тип патрона                          "+type);
      Memo->Lines->Add("Ударов в минуту                      "+IntToStr(count)+" уд/мин");
      Memo->Lines->Add("++++++++++++++++++++++++++++++++++++++++++++++++++");
      Memo->Lines->Add("");
      Memo->Lines->Add("");
    }
        void Get_vals(AnsiString* ptrd)
             {
              ptrd[0] = name;
              ptrd[1] = country;
              ptrd[2] = IntToStr(voltage);
              ptrd[3] = IntToStr(power);
              ptrd[4] = IntToStr(weight);
              ptrd[5] = IntToStr(guarantee);
              ptrd[6] = IntToStr(force);
              ptrd[7] = type;
              ptrd[8] = IntToStr(count);
             }
        void Write_to_file()
             {
              outfile
              <<name.c_str()<<endl
              <<country.c_str()<<endl
              <<voltage<<endl
              <<power<<endl
              <<weight<<endl
              <<guarantee<<endl
              <<force<<endl
              <<type.c_str()<<endl
              <<count<<endl;
             }

        void Read_from_file()
             {
              infile.getline(per1,Ma);
              name = per1;
              infile.getline(per1,Ma);
              country = per1;
              infile.getline(per1,Ma);
              voltage = StrToInt(per1);
              infile.getline(per1,Ma);
              power = StrToInt(per1);
              infile.getline(per1,Ma);
              weight = StrToInt(per1);
              infile.getline(per1,Ma);
              guarantee = StrToInt(per1);
              infile.getline(per1,Ma);
              force = StrToInt(per1);
              infile.getline(per1,Ma);
              type = per1;
              infile.getline(per1,Ma);
              count = StrToInt(per1);
             }
                ~Jackhammers(){}
};

//---------------------Класс контейнер---------------------------------------
class Stack1
{
        private:
                void* data;
                AnsiString name;
                Stack1 *head, *next;
        public:
                Stack1()
                {
                   head  = next = NULL;
                }
                void Add_elem_head(void* x, AnsiString n)
                {
                  Stack1 *el;
                  el = new Stack1;
                  el->data = x;
                  el->name = n;
                  if (head == NULL)
                   {
                    el->next = NULL;
                    head = el;
                   } else
                     {
                      el->next = head;
                      head = el;
                     }
                 }


                void Delete_elem_head()
                 {
                  if(head!=NULL)
                    head = head->next;
                 }

                void Set_data(void* x, AnsiString nname)
                  {
                   bool flag = true;
                   Stack1 *hhead;
                   hhead = head;
                   if (head ==NULL) Add_elem_head(x,nname);
                     else
                        while (hhead !=NULL)
                          {
                            if(hhead->name == nname)
                             {
                               hhead->data = x;
                               flag = false;
                              }
                            hhead = hhead->next;
                           }
                        if (flag) Add_elem_head(x,nname);
                  }

                void* Get_data(AnsiString nname)
                  {
                   Stack1 *hhead;
                   hhead = head;
                   while (hhead !=NULL)
                    {
                     if(hhead->name == nname)
                       {
                        return hhead->data;
                       }
                     hhead = hhead->next;
                    }
                    return NULL;
                  }

                ~Stack1(){};
};

//-------------------------Хранение указателей-------------------------------
template <class T>
class Stack :private Stack1
{
        public:

                Stack()
                {Stack1::Stack1();}
                void Add_elem_head(T x, AnsiString n)
                {Stack1::Add_elem_head(reinterpret_cast<void*>(x),n);}

                void Delete_elem_head()
                 {Stack1::Delete_elem_head();}

                void Set_data(T x, AnsiString n)
                 {Stack1::Set_data(reinterpret_cast<void*>(x),n);}

                T Get_data(AnsiString nname)
                 {
                  if (Stack1::Get_data(nname) != NULL)
                   return reinterpret_cast<T>(Stack1::Get_data(nname));
                  else
                   { dyn_vect* obj=new dyn_vect;
                     return reinterpret_cast<T>(obj);
                   }
                 }

                ~Stack(){};
};

//----------------------------Вектор-----------------------------------------
const MAX = 100;

class dyn_vect
{
 private:
   long size;
   ElectricTools** arr;
 public:
  dyn_vect(long s = MAX): size(s)
   {
    arr = new ElectricTools*[size];
     if(!arr) ShowMessage("Ошибка при создании массива!");
   }

  void Set_one(ElectricTools* x, int num)
   {
    arr[num] = x;
   }

  long length () const {return size;}

  dyn_vect(const dyn_vect& arrr)
   {
       size = arrr.size;
       arr = new ElectricTools*[size];
       for(int i = 0; i<size; i++)
         arr[i] = arrr.arr[i];
   }

  dyn_vect& operator=(const dyn_vect& arrr)
   {
     if (this != &arrr)
      {
       size = arrr.size;
       if (arr) delete[] arr;
       arr = new ElectricTools*[size];
       for(int i = 0; i<size; i++)
         arr[i] = arrr.arr[i];
      }
     return *this;
   }

  void orderVoz(int k, int l, int num, char typ)
   {
    AnsiString mas1[11];
    AnsiString mas2[11];
    this->arr[k]->Get_vals(mas1);
    this->arr[l]->Get_vals(mas2);
    switch(typ)
      {
        case 'i':
          {
           if (StrToInt(mas1[num])>StrToInt(mas2[num]))
             {
              ElectricTools* temp;
              temp = this->arr[k];
              this->arr[k] = this->arr[l];
              this->arr[l] = temp;
             }
          } break;
        case 'a':
          {
           if (mas1[num]>mas2[num])
             {
              ElectricTools* temp;
              temp = this->arr[k];
              this->arr[k] = this->arr[l];
              this->arr[l] = temp;
             }
          } break;
      }
   }

  void orderUb(int k, int l, int num, char typ)
   {
    AnsiString mas1[11];
    AnsiString mas2[11];
    this->arr[k]->Get_vals(mas1);
    this->arr[l]->Get_vals(mas2);
    switch(typ)
      {
        case 'i':
          {
           if (StrToInt(mas1[num])<StrToInt(mas2[num]))
             {
              ElectricTools* temp;
              temp = this->arr[k];
              this->arr[k] = this->arr[l];
              this->arr[l] = temp;
             }
          } break;
        case 'a':
          {
           if (mas1[num]<mas2[num])
             {
              ElectricTools* temp;
              temp = this->arr[k];
              this->arr[k] = this->arr[l];
              this->arr[l] = temp;
             }
          } break;
      }
   }

  void bsortUb(int razm, int numm, char typp)
   {
      for(int i=0; i<razm-1; i++)
        for(int j=i+1; j<razm; j++)
          orderUb(i,j,numm,typp);
   }

  void bsort(int razm, int numm, char typp)
   {
      for(int i=0; i<razm-1; i++)
        for(int j=i+1; j<razm; j++)
          orderVoz(i,j,numm,typp);
   }

  void find(AnsiString findd, TMemo* Memo, int razm, int num, char typ)
   {
    AnsiString mas1[11];
    for(int k=0; k<razm; k++)
     {
      this->arr[k]->Get_vals(mas1);
      switch(typ)
        {
          case 'i':
            {
             if (StrToInt(mas1[num])==StrToInt(findd))
               {this->arr[k]->print(Memo);}
            } break;
          case 'a':
            {
             if (mas1[num]==findd)
               {this->arr[k]->print(Memo);}
            } break;
        }
     }
   }

  void find_Diap(AnsiString find_from, AnsiString find_to, TMemo* Memo, int razm, int num, char typ)
   {
    AnsiString mas1[11];
    for(int k=0; k<razm; k++)
     {
      this->arr[k]->Get_vals(mas1);
      switch(typ)
        {
          case 'i':
            {
             if ((StrToInt(find_from)<=StrToInt(mas1[num]))&&
                 (StrToInt(mas1[num])<=StrToInt(find_to)))
               {this->arr[k]->print(Memo);}
            } break;
          case 'a':
            {
             if ((find_from<=mas1[num])&&(mas1[num]<=find_to))
               {this->arr[k]->print(Memo);}
            } break;
        }
     }
   }  


  ElectricTools* operator[](long n) const
   {
    if(n<0||n>MAX) exit(0);
    return arr[n];
   }
  ~dyn_vect(){};
};

dyn_vect  dyn_vect_screw,dyn_vect_glue,dyn_vect_saw,dyn_vect_jack;
int  kol_screw,kol_glue,kol_saw,kol_jack;
Stack<dyn_vect*> MyStack;
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
  switch (ListBox1->ItemIndex)
   {
    case 0:{
             GroupBox2->Visible=True;
             GroupBox3->Visible=False;
             GroupBox4->Visible=False;
             GroupBox5->Visible=False;
            } break;

    case 1:{
             GroupBox2->Visible=False;
             GroupBox3->Visible=True;
             GroupBox4->Visible=False;
             GroupBox5->Visible=False;
            } break;

    case 2:{
             GroupBox2->Visible=False;
             GroupBox3->Visible=False;
             GroupBox4->Visible=True;
             GroupBox5->Visible=False;
            } break;

    case 3:{
             GroupBox2->Visible=False;
             GroupBox3->Visible=False;
             GroupBox4->Visible=False;
             GroupBox5->Visible=True;
            } break;
   }
}

//---------------------Сохранение в файл-------------------------------------
void write_file()
{
 outfile.open(path);

dyn_vect_screw = *MyStack.Get_data("Screwdrivers");
for(int i = 0; i<kol_screw; i++)
 dyn_vect_screw[i]->Write_to_file();

dyn_vect_glue = *MyStack.Get_data("Decorative");
for(int i = 0; i<kol_glue; i++)
 dyn_vect_glue[i]->Write_to_file();

dyn_vect_saw = *MyStack.Get_data("ElectricSaw");
for(int i = 0; i<kol_saw; i++)
 dyn_vect_saw[i]->Write_to_file();

dyn_vect_jack = *MyStack.Get_data("Jackhammers");
for(int i = 0; i<kol_jack; i++)
 dyn_vect_jack[i]->Write_to_file();

 outfile.close();

 ofstream outfile1("data.bin");
 outfile1
  <<kol_screw<<' '
  <<kol_glue<<' '
  <<kol_saw<<' '
  <<kol_jack<<' ';
}

//------------------------Загрузка из файла----------------------------------
void read_file()
{
try
{
 ifstream infile1("data.bin");
 infile1
  >>kol_screw
  >>kol_glue
  >>kol_saw
  >>kol_jack;

 infile.open(path);
 infile.seekg(0);

 Stack<dyn_vect*> MyStack1;

 for(int i = 0; i<kol_screw; i++)
   {
    Screwdrivers* screw_obj = new Screwdrivers;
    screw_obj->Read_from_file();
    dyn_vect_screw.Set_one(screw_obj,i);
   }

 MyStack1.Add_elem_head(&dyn_vect_screw,"Screwdrivers");

 for(int i = 0; i<kol_glue; i++)
   {
    GlueGuns* glue_obj = new GlueGuns;
    glue_obj->Read_from_file();
    dyn_vect_glue.Set_one(glue_obj,i);
   }

 MyStack1.Add_elem_head(&dyn_vect_glue,"GlueGuns");

 for(int i = 0; i<kol_saw; i++)
   {
    ElectricSaw* saw_obj = new ElectricSaw;
    saw_obj->Read_from_file();
    dyn_vect_saw.Set_one(saw_obj,i);
   }

 MyStack1.Add_elem_head(&dyn_vect_saw,"ElectricSaw");

 for(int i = 0; i<kol_jack; i++)
   {
    Jackhammers* jack_obj = new Jackhammers;
    jack_obj->Read_from_file();
    dyn_vect_jack.Set_one(jack_obj,i);
   }

 MyStack1.Add_elem_head(&dyn_vect_jack,"Jackhammers");

 infile.close();
 MyStack = MyStack1;
}catch(...)
{Application->MessageBox("Ошибка при загрузке!","Файл поврежден!",MB_ICONHAND+MB_OK);}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
 try
  {
   if ((Edit20->Text     != "")&&(Edit1->Text != "")&&(Edit2->Text != "")&&
      (Edit3->Text != "")&&(Edit4->Text != "")&&
      (Edit5->Text     != "")&&(Edit6->Text != "")&&(Edit7->Text != "")&&
      (Edit8->Text != "")&&(Edit9->Text != ""))
       {
        Screwdrivers* ob1=new Screwdrivers(Edit20->Text,Edit1->Text,StrToInt(Edit2->Text),
                             StrToInt(Edit3->Text),StrToInt(Edit4->Text),
                             StrToInt(Edit5->Text),StrToInt(Edit6->Text),
                             StrToInt(Edit7->Text),StrToInt(Edit8->Text),
                             Edit9->Text);
        dyn_vect_screw.Set_one(ob1,kol_screw);
        MyStack.Set_data(&dyn_vect_screw,"Screwdrivers");
        kol_screw++;
        Application->MessageBox("Инструмент добавлен!","",MB_OK);
       } else Application->MessageBox("Заполните все поля!","",MB_ICONHAND+MB_OK);
  }
  catch(EConvertError&)
   {Application->MessageBox("Ошибка данных. Проверьте правильность ввода!","",MB_ICONHAND+MB_OK);}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
Memo1->Clear();
dyn_vect_screw = *MyStack.Get_data("Screwdrivers");
for(int i = 0; i<kol_screw; i++)
 dyn_vect_screw[i]->print(Memo1);

dyn_vect_glue = *MyStack.Get_data("GlueGuns");
for(int i = 0; i<kol_glue; i++)
 dyn_vect_glue[i]->print(Memo1);

dyn_vect_saw = *MyStack.Get_data("ElectricSaw");
for(int i = 0; i<kol_saw; i++)
 dyn_vect_saw[i]->print(Memo1);

dyn_vect_jack = *MyStack.Get_data("Jackhammers");
for(int i = 0; i<kol_jack; i++)
 dyn_vect_jack[i]->print(Memo1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
 try
  {
   if ((Edit20->Text     != "")&&(Edit1->Text != "")&&(Edit2->Text != "")&&
      (Edit3->Text != "")&&(Edit4->Text != "")&&
      (Edit5->Text     != "")&&(Edit10->Text != "")&&(Edit11->Text != "")&&
      (Edit12->Text != "")&&(Edit13->Text != ""))
       {
        GlueGuns* ob1=new GlueGuns(Edit20->Text,Edit1->Text,StrToInt(Edit2->Text),
                             StrToInt(Edit3->Text),StrToInt(Edit4->Text),
                             StrToInt(Edit5->Text),Edit10->Text,
                             StrToInt(Edit11->Text),StrToInt(Edit12->Text),
                             StrToInt(Edit13->Text));
        dyn_vect_glue.Set_one(ob1,kol_glue);
        MyStack.Set_data(&dyn_vect_glue,"GlueGuns");
        kol_glue++;
        Application->MessageBox("Инструмент добавлен!","",MB_OK);
       } else Application->MessageBox("Заполните все поля!","",MB_ICONHAND+MB_OK);
  }
  catch(EConvertError&)
   {Application->MessageBox("Ошибка данных. Проверьте правильность ввода!","",MB_ICONHAND+MB_OK);}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
 try
  {
   if ((Edit20->Text     != "")&&(Edit1->Text != "")&&(Edit2->Text != "")&&
      (Edit3->Text != "")&&(Edit4->Text != "")&&
      (Edit5->Text     != "")&&(Edit14->Text != "")&&(Edit15->Text != "")&&
      (Edit16->Text != ""))
       {
        ElectricSaw* ob1=new ElectricSaw(Edit20->Text,Edit1->Text,StrToInt(Edit2->Text),
                             StrToInt(Edit3->Text),StrToInt(Edit4->Text),
                             StrToInt(Edit5->Text),StrToInt(Edit14->Text),
                             StrToInt(Edit15->Text),Edit16->Text);
        dyn_vect_saw.Set_one(ob1,kol_saw);
        MyStack.Set_data(&dyn_vect_saw,"ElectricSaw");
        kol_saw++;
        Application->MessageBox("Инструмент добавлен!","",MB_OK);
       } else Application->MessageBox("Заполните все поля!","",MB_ICONHAND+MB_OK);
  }
  catch(EConvertError&)
   {Application->MessageBox("Ошибка данных. Проверьте правильность ввода!","",MB_ICONHAND+MB_OK);}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
 try
  {
   if ((Edit20->Text     != "")&&(Edit1->Text != "")&&(Edit2->Text != "")&&
      (Edit3->Text != "")&&(Edit4->Text != "")&&
      (Edit5->Text     != "")&&(Edit17->Text != "")&&(Edit18->Text != "")&&
      (Edit19->Text != ""))
       {
        Jackhammers* ob1=new Jackhammers(Edit20->Text,Edit1->Text,StrToInt(Edit2->Text),
                             StrToInt(Edit3->Text),StrToInt(Edit4->Text),
                             StrToInt(Edit5->Text),StrToInt(Edit17->Text),
                             Edit18->Text,StrToInt(Edit19->Text));
        dyn_vect_jack.Set_one(ob1,kol_jack);
        MyStack.Set_data(&dyn_vect_jack,"Jackhammers");
        kol_jack++;
        Application->MessageBox("Инструмент добавлен!","",MB_OK);
       } else Application->MessageBox("Заполните все поля!","",MB_ICONHAND+MB_OK);
  }
  catch(EConvertError&)
   {Application->MessageBox("Ошибка данных. Проверьте правильность ввода!","",MB_ICONHAND+MB_OK);}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 kol_screw = 0;
 kol_glue = 0;
 kol_saw = 0;
 kol_jack = 0;
 ListBox2->ItemIndex=0;
 Form1->ListBox2Click(Form1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
 if(SaveDialog1->Execute())
  {
   pathAS = SaveDialog1->FileName;
   path = pathAS.c_str();
   write_file();
  }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   pathAS = OpenDialog1->FileName;
   path = pathAS.c_str();
   read_file();
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox2Click(TObject *Sender)
{
  switch (ListBox2->ItemIndex)
   {
    case 0:{
             ComboBox1->Items->Clear();
             ComboBox1->Items->Add("Название");
             ComboBox1->Items->Add("Страна");
             ComboBox1->Items->Add("Напряжение");
             ComboBox1->Items->Add("Мощность");
             ComboBox1->Items->Add("Вес");
             ComboBox1->Items->Add("Гарантия");
             ComboBox1->Items->Add("Ёмкость аккумулятора");
             ComboBox1->Items->Add("Крутящий момент");
             ComboBox1->Items->Add("Число скоростей");
             ComboBox1->Items->Add("Наличие удара");
            } break;

    case 1:{
             ComboBox1->Items->Clear();
             ComboBox1->Items->Add("Название");
             ComboBox1->Items->Add("Страна");
             ComboBox1->Items->Add("Напряжение");
             ComboBox1->Items->Add("Мощность");
             ComboBox1->Items->Add("Вес");
             ComboBox1->Items->Add("Гарантия");
             ComboBox1->Items->Add("Производительность");
             ComboBox1->Items->Add("Время нагрева");
             ComboBox1->Items->Add("Диаметр стержня");
             ComboBox1->Items->Add("Температурный режим");
            } break;

    case 2:{
             ComboBox1->Items->Clear();
             ComboBox1->Items->Add("Название");
             ComboBox1->Items->Add("Страна");
             ComboBox1->Items->Add("Напряжение");
             ComboBox1->Items->Add("Мощность");
             ComboBox1->Items->Add("Вес");
             ComboBox1->Items->Add("Гарантия");
             ComboBox1->Items->Add("Длина шины");
             ComboBox1->Items->Add("Шаг цепи");
             ComboBox1->Items->Add("Плавный пуск");
            } break;

    case 3:{
             ComboBox1->Items->Clear();
             ComboBox1->Items->Add("Название");
             ComboBox1->Items->Add("Страна");
             ComboBox1->Items->Add("Напряжение");
             ComboBox1->Items->Add("Мощность");
             ComboBox1->Items->Add("Вес");
             ComboBox1->Items->Add("Гарантия");
             ComboBox1->Items->Add("Сила удара");
             ComboBox1->Items->Add("Тип патрона");
             ComboBox1->Items->Add("Число ударов/мин");
            } break;
   }
             ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
 if (RadioGroup1->ItemIndex == 0)
  switch (ListBox2->ItemIndex)
   {
    case 0:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_screw.bsort(kol_screw,0,'a'); break;
            case 1: dyn_vect_screw.bsort(kol_screw,1,'a'); break;
            case 2: dyn_vect_screw.bsort(kol_screw,2,'i'); break;
            case 3: dyn_vect_screw.bsort(kol_screw,3,'i'); break;
            case 4: dyn_vect_screw.bsort(kol_screw,4,'i'); break;
            case 5: dyn_vect_screw.bsort(kol_screw,5,'i'); break;
            case 6: dyn_vect_screw.bsort(kol_screw,6,'i'); break;
            case 7: dyn_vect_screw.bsort(kol_screw,7,'i'); break;
            case 8: dyn_vect_screw.bsort(kol_screw,8,'i'); break;
            case 9: dyn_vect_screw.bsort(kol_screw,9,'a'); break;
           };
            Memo2->Clear();
            dyn_vect_screw = *MyStack.Get_data("Screwdrivers");
            for(int i = 0; i<kol_screw; i++)
              dyn_vect_screw[i]->print(Memo2);
            } break;
    case 1:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_glue.bsort(kol_glue,0,'a'); break;
            case 1: dyn_vect_glue.bsort(kol_glue,1,'a'); break;
            case 2: dyn_vect_glue.bsort(kol_glue,2,'i'); break;
            case 3: dyn_vect_glue.bsort(kol_glue,3,'i'); break;
            case 4: dyn_vect_glue.bsort(kol_glue,4,'i'); break;
            case 5: dyn_vect_glue.bsort(kol_glue,5,'i'); break;
            case 6: dyn_vect_glue.bsort(kol_glue,6,'a'); break;
            case 7: dyn_vect_glue.bsort(kol_glue,7,'i'); break;
            case 8: dyn_vect_glue.bsort(kol_glue,8,'i'); break;
            case 9: dyn_vect_glue.bsort(kol_glue,9,'i'); break;
           };
            Memo2->Clear();
            dyn_vect_glue = *MyStack.Get_data("GlueGuns");
            for(int i = 0; i<kol_glue; i++)
             dyn_vect_glue[i]->print(Memo2);
           } break;
    case 2:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_saw.bsort(kol_saw,0,'a'); break;
            case 1: dyn_vect_saw.bsort(kol_saw,1,'a'); break;
            case 2: dyn_vect_saw.bsort(kol_saw,2,'i'); break;
            case 3: dyn_vect_saw.bsort(kol_saw,3,'i'); break;
            case 4: dyn_vect_saw.bsort(kol_saw,4,'i'); break;
            case 5: dyn_vect_saw.bsort(kol_saw,5,'i'); break;
            case 6: dyn_vect_saw.bsort(kol_saw,6,'i'); break;
            case 7: dyn_vect_saw.bsort(kol_saw,7,'i'); break;
            case 8: dyn_vect_saw.bsort(kol_saw,8,'a'); break;
           };
            Memo2->Clear();
            dyn_vect_saw = *MyStack.Get_data("ElectricSaw");
            for(int i = 0; i<kol_saw; i++)
             dyn_vect_saw[i]->print(Memo2);
           } break;
    case 3:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_jack.bsort(kol_jack,0,'a'); break;
            case 1: dyn_vect_jack.bsort(kol_jack,1,'a'); break;
            case 2: dyn_vect_jack.bsort(kol_jack,2,'i'); break;
            case 3: dyn_vect_jack.bsort(kol_jack,3,'i'); break;
            case 4: dyn_vect_jack.bsort(kol_jack,4,'i'); break;
            case 5: dyn_vect_jack.bsort(kol_jack,5,'i'); break;
            case 6: dyn_vect_jack.bsort(kol_jack,6,'i'); break;
            case 7: dyn_vect_jack.bsort(kol_jack,7,'a'); break;
            case 8: dyn_vect_jack.bsort(kol_jack,8,'i'); break;
           };
            Memo2->Clear();
            dyn_vect_jack = *MyStack.Get_data("Jackhammers");
            for(int i = 0; i<kol_jack; i++)
             dyn_vect_jack[i]->print(Memo2);
           } break;
   };

 if (RadioGroup1->ItemIndex == 1)
  switch (ListBox2->ItemIndex)
   {
    case 0:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_screw.bsortUb(kol_screw,0,'a'); break;
            case 1: dyn_vect_screw.bsortUb(kol_screw,1,'a'); break;
            case 2: dyn_vect_screw.bsortUb(kol_screw,2,'i'); break;
            case 3: dyn_vect_screw.bsortUb(kol_screw,3,'i'); break;
            case 4: dyn_vect_screw.bsortUb(kol_screw,4,'i'); break;
            case 5: dyn_vect_screw.bsortUb(kol_screw,5,'i'); break;
            case 6: dyn_vect_screw.bsortUb(kol_screw,6,'i'); break;
            case 7: dyn_vect_screw.bsortUb(kol_screw,7,'i'); break;
            case 8: dyn_vect_screw.bsortUb(kol_screw,8,'i'); break;
            case 9: dyn_vect_screw.bsortUb(kol_screw,9,'a'); break;
           };
            Memo2->Clear();
            dyn_vect_screw = *MyStack.Get_data("Screwdrivers");
            for(int i = 0; i<kol_screw; i++)
              dyn_vect_screw[i]->print(Memo2);
            } break;
    case 1:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_glue.bsortUb(kol_glue,0,'a'); break;
            case 1: dyn_vect_glue.bsortUb(kol_glue,1,'a'); break;
            case 2: dyn_vect_glue.bsortUb(kol_glue,2,'i'); break;
            case 3: dyn_vect_glue.bsortUb(kol_glue,3,'i'); break;
            case 4: dyn_vect_glue.bsortUb(kol_glue,4,'i'); break;
            case 5: dyn_vect_glue.bsortUb(kol_glue,5,'i'); break;
            case 6: dyn_vect_glue.bsortUb(kol_glue,6,'a'); break;
            case 7: dyn_vect_glue.bsortUb(kol_glue,7,'i'); break;
            case 8: dyn_vect_glue.bsortUb(kol_glue,8,'i'); break;
            case 9: dyn_vect_glue.bsortUb(kol_glue,9,'i'); break;
           };
            Memo2->Clear();
            dyn_vect_glue = *MyStack.Get_data("GlueGuns");
            for(int i = 0; i<kol_glue; i++)
             dyn_vect_glue[i]->print(Memo2);
           } break;
    case 2:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_saw.bsortUb(kol_saw,0,'a'); break;
            case 1: dyn_vect_saw.bsortUb(kol_saw,1,'a'); break;
            case 2: dyn_vect_saw.bsortUb(kol_saw,2,'i'); break;
            case 3: dyn_vect_saw.bsortUb(kol_saw,3,'i'); break;
            case 4: dyn_vect_saw.bsortUb(kol_saw,4,'i'); break;
            case 5: dyn_vect_saw.bsortUb(kol_saw,5,'i'); break;
            case 6: dyn_vect_saw.bsortUb(kol_saw,6,'i'); break;
            case 7: dyn_vect_saw.bsortUb(kol_saw,7,'i'); break;
            case 8: dyn_vect_saw.bsortUb(kol_saw,8,'a'); break;
           };
            Memo2->Clear();
            dyn_vect_saw = *MyStack.Get_data("ElectricSaw");
            for(int i = 0; i<kol_saw; i++)
             dyn_vect_saw[i]->print(Memo2);
           } break;
    case 3:{
           switch (ComboBox1->ItemIndex)
           {
            case 0: dyn_vect_jack.bsortUb(kol_jack,0,'a'); break;
            case 1: dyn_vect_jack.bsortUb(kol_jack,1,'a'); break;
            case 2: dyn_vect_jack.bsortUb(kol_jack,2,'i'); break;
            case 3: dyn_vect_jack.bsortUb(kol_jack,3,'i'); break;
            case 4: dyn_vect_jack.bsortUb(kol_jack,4,'i'); break;
            case 5: dyn_vect_jack.bsortUb(kol_jack,5,'i'); break;
            case 6: dyn_vect_jack.bsortUb(kol_jack,6,'i'); break;
            case 7: dyn_vect_jack.bsortUb(kol_jack,7,'a'); break;
            case 8: dyn_vect_jack.bsortUb(kol_jack,8,'i'); break;
           };
            Memo2->Clear();
            dyn_vect_jack = *MyStack.Get_data("Jackhammers");
            for(int i = 0; i<kol_jack; i++)
             dyn_vect_jack[i]->print(Memo2);
           } break;
   };
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RadioGroup2Click(TObject *Sender)
{
switch (RadioGroup2->ItemIndex)
 {
  case 0: {Panel1->Visible=true; Panel2->Visible=false;}break;
  case 1: {Panel1->Visible=false; Panel2->Visible=true;}break;
 }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
Memo2->Clear();
 if (RadioGroup2->ItemIndex == 0){
 if (Edit21->Text == "") ShowMessage("Введите значение для поиска!");
  if (Edit21->Text !="")
   switch (ListBox2->ItemIndex)
    {

     case 0:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,0,'a'); break;
                case 1: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,1,'a'); break;
                case 2: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,2,'i'); break;
                case 3: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,3,'i'); break;
                case 4: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,4,'i'); break;
                case 5: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,5,'i'); break;
                case 6: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,6,'i'); break;
                case 7: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,7,'i'); break;
                case 8: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,8,'i'); break;
                case 9: dyn_vect_screw.find(Edit21->Text,Memo2,kol_screw,9,'a'); break;
               };
            } break;
     case 1:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,0,'a'); break;
                case 1: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,1,'a'); break;
                case 2: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,2,'i'); break;
                case 3: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,3,'i'); break;
                case 4: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,4,'i'); break;
                case 5: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,5,'i'); break;
                case 6: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,6,'a'); break;
                case 7: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,7,'i'); break;
                case 8: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,8,'i'); break;
                case 9: dyn_vect_glue.find(Edit21->Text,Memo2,kol_glue,9,'i'); break;
               };
            } break;
     case 2:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,0,'a'); break;
                case 1: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,1,'a'); break;
                case 2: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,2,'i'); break;
                case 3: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,3,'i'); break;
                case 4: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,4,'i'); break;
                case 5: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,5,'i'); break;
                case 6: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,6,'i'); break;
                case 7: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,7,'i'); break;
                case 8: dyn_vect_saw.find(Edit21->Text,Memo2,kol_saw,8,'a'); break;
               };
            } break;
     case 3:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,0,'a'); break;
                case 1: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,1,'a'); break;
                case 2: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,2,'i'); break;
                case 3: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,3,'i'); break;
                case 4: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,4,'i'); break;
                case 5: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,5,'i'); break;
                case 6: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,6,'i'); break;
                case 7: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,7,'a'); break;
                case 8: dyn_vect_jack.find(Edit21->Text,Memo2,kol_jack,8,'i'); break;
               };
            } break;
   }; }


 if (RadioGroup2->ItemIndex == 1)  {
 if ((Edit22->Text == "")||(Edit23->Text == "")) ShowMessage("Введите оба значения для поиска!");
  if ((Edit22->Text != "")&&(Edit23->Text != ""))
   switch (ListBox2->ItemIndex)
    {
     Memo2->Clear();
     case 0:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,0,'a'); break;
                case 1: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,1,'a'); break;
                case 2: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,2,'i'); break;
                case 3: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,3,'i'); break;
                case 4: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,4,'i'); break;
                case 5: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,5,'i'); break;
                case 6: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,6,'i'); break;
                case 7: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,7,'i'); break;
                case 8: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,8,'i'); break;
                case 9: dyn_vect_screw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_screw,9,'a'); break;
              };
            } break;
     case 1:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,0,'a'); break;
                case 1: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,1,'a'); break;
                case 2: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,2,'i'); break;
                case 3: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,3,'i'); break;
                case 4: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,4,'i'); break;
                case 5: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,5,'i'); break;
                case 6: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,6,'a'); break;
                case 7: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,7,'i'); break;
                case 8: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,8,'i'); break;
                case 9: dyn_vect_glue.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_glue,9,'i'); break;
               };
            } break;
     case 2:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,0,'a'); break;
                case 1: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,1,'a'); break;
                case 2: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,2,'i'); break;
                case 3: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,3,'i'); break;
                case 4: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,4,'i'); break;
                case 5: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,5,'i'); break;
                case 6: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,6,'i'); break;
                case 7: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,7,'i'); break;
                case 8: dyn_vect_saw.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_saw,8,'a'); break;
               };
            } break;
     case 3:{
              switch (ComboBox1->ItemIndex)
               {
                case 0: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,0,'a'); break;
                case 1: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,1,'a'); break;
                case 2: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,2,'i'); break;
                case 3: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,3,'i'); break;
                case 4: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,4,'i'); break;
                case 5: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,5,'i'); break;
                case 6: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,6,'i'); break;
                case 7: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,7,'a'); break;
                case 8: dyn_vect_jack.find_Diap(Edit22->Text, Edit23->Text,Memo2,kol_jack,8,'i'); break;
               };
            } break;
  };
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
        Form1->Button6->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        Form1->Button7->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
        Form1->Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
        Form2->ShowModal();        
}
//---------------------------------------------------------------------------

