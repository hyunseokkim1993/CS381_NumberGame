#include "numbergame.h"
#include <iostream>
#include <tuple>
#include <queue>

struct Node
{
	std::vector<int>field;
	std::vector<std::tuple<unsigned, unsigned>> steps;
	Node() : field(std::vector<int>()), steps(std::vector<std::tuple<unsigned, unsigned>>()) {}
	Node(std::vector<int>f, std::vector<std::tuple<unsigned, unsigned>>s) : field(f), steps(s){}
};

std::vector<std::tuple<unsigned, unsigned>> SolveNumbergameBFS(std::string const& filename)
{
	/////////////////////////////////////////////////
	///File Input
	/////////////////////////////////////////////////
	std::ifstream file(filename);
	if (!file.good())
	{
		std::cout << "failed to open file";
	}
	std::vector<int>list;

	int input;
	file >> input;
	while (file.good() && !file.eof())
	{
		list.push_back(input);
		file >> input;
	}
	int width = list.at(0);


	/////////////////////////////////////////////////
	///Set up
	/////////////////////////////////////////////////
	std::vector<std::tuple<unsigned, unsigned>> result;

	list.erase(list.begin());

	Node root;
	root.field = list;
	std::queue<Node>que;
	que.push(root);

	bool IsSolutionFound = false;

	while (!que.empty() && !IsSolutionFound)
	{
		Node CurrNode = que.front();

		

		/*for(int i=0; i<CurrNode.field.size(); ++i)
		{
			if(CurrNode.field.at(i) != 0)
			{
				break;
			}
			else if(i == CurrNode.field.size()-1 && CurrNode.field.at(i) == 0)
			{
				IsSolutionFound = true;
				return CurrNode.steps;
			}
		}*/

		
		/////////////////////////////////////////////////
		///Horizontal Check
		/////////////////////////////////////////////////
		for (unsigned i = 0; i < CurrNode.field.size() - 1; ++i)
		{
			unsigned pos1 = i;
			unsigned pos2 = i + 1;
			bool checking = false;
			while(!checking)
			{
				if(CurrNode.field.at(pos2) == 0 && pos2 < CurrNode.field.size()-1)
				{
					pos2 += 1;
				}
				else
				{
					checking = true;
				}
			}
			
			if (CurrNode.field.at(pos1) != 0)
			{
				//if adjacent positions are identical or adds up to 10
				if (CurrNode.field.at(pos1) == CurrNode.field.at(pos2) ||
					CurrNode.field.at(pos1) + CurrNode.field.at(pos2) == 10)
				{


					
					//New node;
					Node NewNode;
					//add current positions to trace back later
					std::tuple<unsigned, unsigned>step = std::make_tuple(pos1, pos2);
					NewNode.steps = CurrNode.steps;
					NewNode.steps.push_back(step);

					//update the field with positions take out
					std::vector<int>newField;
					for (unsigned j = 0; j < CurrNode.field.size(); ++j)
					{
						if (j != pos1 && j != pos2)
						{
							newField.push_back(CurrNode.field.at(j));
						}
						else
						{
							newField.push_back(0);
						}
					}
					for (unsigned k = 0; k < newField.size(); ++k)
					{
						if (newField.at(k) != 0)
						{
							break;
						}
						else if (k == newField.size() - 1 && newField.at(k) == 0)
						{
							IsSolutionFound = true;
							return NewNode.steps;
						}
					}
					if(newField.back() == 0)
					{
						newField.pop_back();
					}
					NewNode.field = newField;
					que.push(NewNode);
				}
			}
		}//END OF HORIZONTAL CHECK

		
		/////////////////////////////////////////////////
		///Vertical Check
		/////////////////////////////////////////////////
		for (unsigned i = 0; i < CurrNode.field.size() - width; ++i)
		{
			for (unsigned j = i + width; j < CurrNode.field.size(); j += width)
			{
				unsigned pos1 = i;
				unsigned pos2 = j;
				
				if(CurrNode.field.at(pos1) != 0)
				{
					if(CurrNode.field.at(pos1) == CurrNode.field.at(pos2) ||
						CurrNode.field.at(pos1) + CurrNode.field.at(pos2) == 10)
					{
						bool isValidNeighbor = true;

						
						
							for(unsigned a =pos1+width; a < pos2; a+=width)
							{
								if (a != 0)
									isValidNeighbor = false;
							}
						
						if (isValidNeighbor)
						{
							//New node;
							Node NewNode;
							//add current positions to trace back later
							std::tuple<unsigned, unsigned>step = std::make_tuple(pos1, pos2);
							NewNode.steps = CurrNode.steps;
							NewNode.steps.push_back(step);

							//update the field with positions take out
							std::vector<int>newField;
							for (unsigned k = 0; k < CurrNode.field.size(); ++k)
							{
								if (k != pos1 && k != pos2)
								{
									newField.push_back(CurrNode.field.at(k));
								}
								else
								{
									newField.push_back(0);
								}
							}
							for (unsigned z = 0; z < newField.size(); ++z)
							{
								if (newField.at(z) != 0)
								{
									break;
								}
								else if (z == newField.size() - 1 && newField.at(z) == 0)
								{
									IsSolutionFound = true;
									return NewNode.steps;
								}
							}
							if (newField.back() == 0)
							{
								newField.pop_back();
							}
							NewNode.field = newField;
							que.push(NewNode);
						}
					}
				}
			}
		}//END OF VERTICAL CHECK
		

		/////////////////////////////////////////////////
		///Check Check
		/////////////////////////////////////////////////
		Node NewNode;
		std::vector<int>copyList;
		for (auto& it : CurrNode.field)
		{
			if(it != 0)
			{
				copyList.push_back(it);
			}
		}
		//append fields
		NewNode.field = CurrNode.field;
		NewNode.field.insert(NewNode.field.end(), copyList.begin(), copyList.end());
		if (NewNode.field.back() == 0)
		{
			NewNode.field.pop_back();
		}
		std::tuple<unsigned, unsigned>step = std::make_tuple(0,0);
		NewNode.steps = CurrNode.steps;
		NewNode.steps.push_back(step);
		que.push(NewNode);

		
		/////////////////////////////////////////////////
		///End of loop
		/////////////////////////////////////////////////
		que.pop();



	}


	return result;
}
