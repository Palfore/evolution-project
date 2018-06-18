#ifndef AxonGene_H
#define AxonGene_H

#include "Gene.h"


class AxonGene : public Gene {
    public:
        static constexpr char symbol = 'N';

        int a;
        int b;
        int layer;
        double weight;

        AxonGene(int a_t, int b_t, int layer_t, double weight_t);
        AxonGene(std::string representation);
        AxonGene(const AxonGene& other);
        virtual ~AxonGene();

        virtual Gene* clone() const;
        virtual std::string toString() const override;
        void mutate(Genome& genome);

};

#endif // AxonGene_H
