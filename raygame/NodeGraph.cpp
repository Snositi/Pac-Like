#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	// Find a path from start to end (The current implementation is obviously insufficient)
	std::deque<Node*> path;
	if (!start || !end)
		return std::deque<Node*>();

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = nullptr;
	//Create an open list
	//Create a closed list
	std::deque<Node*> open;
	std::deque<Node*> closed;
	//Add start to the open list
	open.push_back(start);
	//Loop while the open list is not empty
	while (!open.empty())
	{
		//Sort the items in the open list by the g score
		for (int i = 0; i < open.size(); i++)
		{
			for (int j = open.size() - 1; j > i; j--)
			{
				if (open[j]->fScore < open[j - 1]->fScore) {
					Node* temp = open[j];
					open[j] = open[j - 1];
					open[j - 1] = temp;
				}
			}
		}
		//Set the iterator to be the first item in the open list
		currentNode = open[0];
		//Check if the iterator is pointing to the goal node
		if (currentNode == end)
		{
			//Return the new path found
			while (currentNode->previous != nullptr)
			{
				path.push_front(currentNode);
				Node* nextNode = currentNode;
				currentNode = currentNode->previous;
				nextNode->previous = nullptr;
			}
			return path;
		}//end if statement

		//Pop the first item off the open list
		open.pop_front();
		//Add the first item to the closed list
		closed.push_back(currentNode);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = currentNode->connections[i].target;

			//Check if current node is not in the closed list
			if (!inList(closed, currentEdgeEnd))
			{
				//Create an int and set it to be the g score of the iterator plus the cost of the edge
				float gScore = currentNode->gScore + currentNode->connections[i].cost;
				//Create a float and set it to be the h score of the node at the end of the edge
				float hScore = (currentEdgeEnd->position - end->position).getMagnitude();
				//Create a float for the f score and set it to be the g score combined with the h score
				float fScore = gScore + hScore;

				if (!inList(open, currentEdgeEnd))
				{//Check if the node at the end of the edge is not in the open list

						//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = gScore;
					//Set the nodes h score to be the h score calculated earlier
					currentEdgeEnd->hScore = hScore;
					//Set its nodes f score to be the f score calculated earlier
					currentEdgeEnd->fScore = fScore;
					//Set the nodes previous to be the iterator
					currentEdgeEnd->previous = currentNode;
					//Add the node to the open list
					open.push_back(currentEdgeEnd);
				}
				else if (currentNode->fScore < currentEdgeEnd->fScore)
				{//Otherwise if the f score is less than the node at the end of the edge's f score...
						//Set the nodes g score to be the g score calculated earlier
						//Set its g score to be the g score calculated earlier
					currentEdgeEnd->gScore = gScore;
					//Set the nodes h score to be the h score calculated earlier
					currentEdgeEnd->hScore = hScore;
					//Set its f score to be the f score calculated earlier
					currentEdgeEnd->fScore = fScore;
					//Set its previous to be the current node
					//Set the nodes previous to be the iterator
					currentEdgeEnd->previous = currentNode;
				}
			}
			//end if statement
		}//end loop
	}//end loop
	return path;
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}

bool NodeGraph::inList(std::deque<Node*> list, Node* node)
{
	//iterates through entire deque List
	for (int i = 0; i < list.size(); i++)
		//Checks to see if the node at the current iteration is the desired node
		if (list[i] == node)
		{
			//If this is the node, return true
			return true;
		}
	//If the function made it this far, the node was not in the list
	return false;
}
