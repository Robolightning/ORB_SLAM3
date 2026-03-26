#ifndef ORBVOCABULARYWITHTEXTIO_H
#define ORBVOCABULARYWITHTEXTIO_H

#include "ORBVocabulary.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

namespace ORB_SLAM3
{

    class ORBVocabularyWithTextIO : public ORBVocabulary
    {
    public:
        ORBVocabularyWithTextIO() : ORBVocabulary() {}
        ORBVocabularyWithTextIO(int k, int L, DBoW2::WeightingType weighting = DBoW2::TF_IDF, DBoW2::ScoringType scoring = DBoW2::L1_NORM)
            : ORBVocabulary(k, L, weighting, scoring) {}

        bool loadFromTextFile(const std::string& filename)
        {
            std::ifstream f(filename.c_str());
            if (!f.is_open())
                return false;

            m_words.clear();
            m_nodes.clear();

            std::string s;
            std::getline(f, s);
            std::stringstream ss;
            ss << s;
            ss >> m_k;
            ss >> m_L;
            int n1, n2;
            ss >> n1;
            ss >> n2;

            if (m_k < 0 || m_k > 20 || m_L < 1 || m_L > 10 || n1 < 0 || n1 > 5 || n2 < 0 || n2 > 3)
            {
                std::cerr << "Vocabulary loading failure: This is not a correct text file!" << std::endl;
                return false;
            }

            m_scoring = (DBoW2::ScoringType)n1;
            m_weighting = (DBoW2::WeightingType)n2;
            createScoringObject();

            // nodes
            int expected_nodes = (int)((std::pow((double)m_k, (double)m_L + 1) - 1) / (m_k - 1));
            m_nodes.reserve(expected_nodes);
            m_words.reserve((int)std::pow((double)m_k, (double)m_L + 1));

            m_nodes.resize(1);
            m_nodes[0].id = 0;
            while (!f.eof())
            {
                std::string snode;
                std::getline(f, snode);
                if (snode.empty())
                    continue;
                std::stringstream ssnode;
                ssnode << snode;

                int nid = m_nodes.size();
                m_nodes.resize(m_nodes.size() + 1);
                m_nodes[nid].id = nid;

                int pid;
                ssnode >> pid;
                m_nodes[nid].parent = pid;
                m_nodes[pid].children.push_back(nid);

                int nIsLeaf;
                ssnode >> nIsLeaf;

                std::stringstream ssd;
                for (int iD = 0; iD < DBoW2::FORB::L; ++iD)
                {
                    std::string sElement;
                    ssnode >> sElement;
                    ssd << sElement << " ";
                }
                DBoW2::FORB::fromString(m_nodes[nid].descriptor, ssd.str());

                ssnode >> m_nodes[nid].weight;

                if (nIsLeaf > 0)
                {
                    int wid = m_words.size();
                    m_words.resize(wid + 1);
                    m_nodes[nid].word_id = wid;
                    m_words[wid] = &m_nodes[nid];
                }
                else
                {
                    m_nodes[nid].children.reserve(m_k);
                }
            }

            return true;
        }

        void saveToTextFile(const std::string& filename) const
        {
            std::ofstream f(filename.c_str());
            if (!f.is_open())
                return;

            f << m_k << " " << m_L << " " << m_scoring << " " << m_weighting << std::endl;

            for (size_t i = 1; i < m_nodes.size(); ++i)
            {
                const Node& node = m_nodes[i];
                f << node.parent << " ";
                f << (node.isLeaf() ? 1 : 0) << " ";
                f << DBoW2::FORB::toString(node.descriptor) << " " << (double)node.weight << std::endl;
            }

            f.close();
        }
    };

} // namespace ORB_SLAM3

#endif