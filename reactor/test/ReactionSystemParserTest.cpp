#include "ReactionSystemParser.h" // Include the code that we are testing
#include <gtest/gtest.h> // Include the google test framework

using namespace reactor;

class ReactionSystemParserTest: public ::testing::Test {
protected:
	ReactionSystemParser parser;
	ReactionSystemParserTest():
		parser()
	{
	};
};

TEST_F(ReactionSystemParserTest, ParserCanStart) {
  std::istringstream buffer("");
  std::shared_ptr<ReactionSystem> system = parser.FromStream(buffer);	
  EXPECT_EQ(0,system->GetSpecies().size());
}

TEST_F(ReactionSystemParserTest, ParserCanCreateSpecies) {
  // Define your reaction system file format sensibly here
  std::istringstream buffer(
			    "A + B > 2.0 > C + D\n"
			    "C > 3.0 > E + F\n"
			    "A > 5.0 > C\n"		
			    );
  std::shared_ptr<ReactionSystem> system = parser.FromStream(buffer);
  ASSERT_EQ(6,system->GetSpecies().size());
  EXPECT_EQ("A",system->GetSpecies()[0]->GetName());
  EXPECT_EQ("B",system->GetSpecies()[1]->GetName());
  EXPECT_EQ("C",system->GetSpecies()[2]->GetName());
  EXPECT_EQ("D",system->GetSpecies()[3]->GetName());
  EXPECT_EQ("E",system->GetSpecies()[4]->GetName());
  EXPECT_EQ("F",system->GetSpecies()[5]->GetName());
}

TEST_F(ReactionSystemParserTest, ParserCanCreateReactions) {
  // Define your reaction system file format sensibly here
  std::istringstream buffer(
			    "A + B > 2.0 > C + D\n"
			    "C > 3.0 > E + F\n"
			    "A > 5.0 > C\n"		
			    );
  std::shared_ptr<ReactionSystem> system = parser.FromStream(buffer);
  ASSERT_EQ(3,system->GetReactions().size());
  EXPECT_EQ(2.0,system->GetReactions()[0]->GetReactionRate());
  EXPECT_EQ(3.0,system->GetReactions()[1]->GetReactionRate());
  EXPECT_EQ(5.0,system->GetReactions()[2]->GetReactionRate());
}

TEST_F(ReactionSystemParserTest, ParserReactionsHaveAppropriateSpecies) {
  // Define your reaction system file format sensibly here
  std::istringstream buffer(
			    "A + B > 2.0 > C + D\n"
			    "C > 3.0 > E + F\n"
			    "A > 5.0 > C\n"		
			    );
  std::shared_ptr<ReactionSystem> system = parser.FromStream(buffer);
  
  ASSERT_EQ(3,system->GetReactions().size());
  ASSERT_EQ(2,system->GetReactions()[0]->GetReactants().size());
  ASSERT_EQ(2,system->GetReactions()[0]->GetProducts().size());
  ASSERT_EQ(1,system->GetReactions()[1]->GetReactants().size());
  ASSERT_EQ(2,system->GetReactions()[1]->GetProducts().size());
  ASSERT_EQ(1,system->GetReactions()[2]->GetReactants().size());
  ASSERT_EQ(1,system->GetReactions()[2]->GetProducts().size());
  
  EXPECT_EQ(system->GetReactions()[0]->GetReactants()[0],system->GetSpecies()[0]);
  EXPECT_EQ(system->GetReactions()[0]->GetReactants()[1],system->GetSpecies()[1]);
  EXPECT_EQ(system->GetReactions()[0]->GetProducts()[0],system->GetSpecies()[2]);
  EXPECT_EQ(system->GetReactions()[0]->GetProducts()[1],system->GetSpecies()[3]);
  
  EXPECT_EQ(system->GetReactions()[1]->GetReactants()[0],system->GetSpecies()[2]);
  EXPECT_EQ(system->GetReactions()[1]->GetProducts()[0],system->GetSpecies()[4]);
  EXPECT_EQ(system->GetReactions()[1]->GetProducts()[1],system->GetSpecies()[5]);
  
  EXPECT_EQ(system->GetReactions()[2]->GetReactants()[0],system->GetSpecies()[0]);
  EXPECT_EQ(system->GetReactions()[2]->GetProducts()[0],system->GetSpecies()[2]);

}

TEST_F(ReactionSystemParserTest, ParserCanFindExistingSpecies) {
  auto system = std::make_shared<ReactionSystem>();
  auto ca=parser.NewOrFind(system,"Ca");
  auto ca2=parser.NewOrFind(system,"Ca");
  auto c=parser.NewOrFind(system,"C");
  EXPECT_EQ(ca,ca2);
  EXPECT_NE(ca,c);
  ASSERT_EQ(2,system->GetSpecies().size());
  EXPECT_EQ(system->GetSpecies()[0],ca);
  EXPECT_EQ(system->GetSpecies()[0],ca2);
  EXPECT_EQ(system->GetSpecies()[1],c);
}

TEST_F(ReactionSystemParserTest, ParseLine) {
  // Define one reaction from your file format sensibly here
  std::string source("A + B > 2.0 > C + D");
  std::vector<std::string> reactant_names;
  std::vector<std::string> product_names;
  double rate(0.0);
  parser.ParseLine(source, reactant_names, product_names, rate);
  std::vector<std::string> expected_reactant_names;
  std::vector<std::string> expected_product_names;
  expected_reactant_names.push_back("A");
  expected_reactant_names.push_back("B");
  expected_product_names.push_back("C");
  expected_product_names.push_back("D");
  EXPECT_EQ(expected_product_names,product_names);
  EXPECT_EQ(expected_reactant_names,reactant_names);
  EXPECT_EQ(2.0,rate);
}

int main(int argc, char **argv) { // A main function scaffold to call the tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
