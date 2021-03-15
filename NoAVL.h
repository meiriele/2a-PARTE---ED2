#ifndef NOAVL_H
#define NOAVL_H


class NoAVL
{
    public:
        NoAVL();
        ~NoAVL();
        int getID();
        int getFatbalance();
        NoAVL* getDir();
        NoAVL* getEsq();
        NoAVL* getPai();
        void setID(int val);
        void setFatbalance(int val);
        void setDir(NoAVL* p);
        void setEsq(NoAVL* p);
        void setPai(NoAVL* p);

    protected:

    private:
        int id;
        NoAVL* dir;
        NoAVL* esq;
        NoAVL* pai;
        int fatbalance;
};

#endif // NOAVL_H
