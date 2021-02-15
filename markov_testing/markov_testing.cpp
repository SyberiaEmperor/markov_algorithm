#include "pch.h"
#include "CppUnitTest.h"
#include "../markov_algorithm/terminal.h"
#include "../markov_algorithm/terminal.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace markovtesting
{
	TEST_CLASS(markovtesting)
	{
	public:
		
		TEST_METHOD(ParseTest)
		{
			parser p;

			vector<string> system = {
				"a->b",
				"->b",
				"a->",
				"->",
				"h=>f",
				"=>f",
				"h=>",
				"=>"
			};

			auto subs = p.get_subs(system);

			assert(subs[0].from == "a" && subs[0].to == "b" && !subs[0].is_final);
			assert(subs[1].from == "" && subs[1].to == "b" && !subs[1].is_final);
			assert(subs[2].from == "a" && subs[2].to == "" && !subs[2].is_final);
			assert(subs[3].from == "" && subs[3].to == "" && !subs[3].is_final);
			assert(subs[4].from == "h" && subs[4].to == "f" && subs[4].is_final);
			assert(subs[5].from == "" && subs[5].to == "f" && subs[5].is_final);
			assert(subs[6].from == "h" && subs[6].to == "" && subs[6].is_final);
			assert(subs[7].from == "" && subs[7].to == "" && subs[7].is_final);

			system = {
				"a->bg0->",
			};

			Assert::ExpectException<invalid_argument>([&p, &system]() {p.get_subs(system); });

			system = {
				"gob",
			};

			Assert::ExpectException<invalid_argument>([&p, &system]() {p.get_subs(system); });

			system = {
				">->->",
			};

			Assert::ExpectException<invalid_argument>([&p, &system]() {p.get_subs(system); });
		}

		TEST_METHOD(MarkovTest1)
		{
			parser p;
			markov_engine me;
			string w = "";

			vector<string> s1 = {
				"ab->a",
				"b->",
				"a->b",
			};

			me.set_system(p.get_subs(s1));

			w = "bbaab";
			assert(me.apply_word(w) == "");
			w = "aabbbaa";
			assert(me.apply_word(w) == "");
			w = "bababab";
			assert(me.apply_word(w) == "");

			s1 = {
				"ab->a",
				"b=>",
				"a->b",
			};

			me.set_system(p.get_subs(s1));

			w = "bbaab";
			assert(me.apply_word(w) == "baa");
			w = "aabbbaa";
			assert(me.apply_word(w) == "aaa");
			w = "bababab";
			assert(me.apply_word(w) == "aaa");
			w = "abbabba";
			assert(me.apply_word(w) == "aa");

			s1 = {
				"ba->a",
				"bb->b",
				"ab->",
				"=>b"
			};

			me.set_system(p.get_subs(s1));

			w = "bbaab";
			assert(me.apply_word(w) == "ba");
			w = "aabbbaa";
			assert(me.apply_word(w) == "baaaa");
			w = "bababab";
			assert(me.apply_word(w) == "baa");

		}

		TEST_METHOD(MarkovTest2)
		{
			parser p;
			markov_engine me;
			string w = "";

			vector<string> s1 = {
				"a->",
				"b->",
				"c->",
			};

			me.set_system(p.get_subs(s1));

			w = "bbaab";
			assert(me.apply_word(w) == "");
			w = "aabbbaa";
			assert(me.apply_word(w) == "");
			w = "bababab";
			assert(me.apply_word(w) == "");

			s1 = {
				"*1->1*",
				"*0->0*",
				"1*->#1",
				"0*->#0",
				"1#->#0",
				"*=>",
				"0#=>1",
				"#=>1",
				"->*",
			};

			me.set_system(p.get_subs(s1));

			w = "11";
			assert(me.apply_word(w) == "101");
			w = "1";
			assert(me.apply_word(w) == "11");
			w = "111";
			assert(me.apply_word(w) == "1001");


			s1 = {
				"ba->a",
				"bb->b",
				"ab->",
				"=>b"
			};

			me.set_system(p.get_subs(s1));

			w = "bbaab";
			assert(me.apply_word(w) == "ba");
			w = "aabbbaa";
			assert(me.apply_word(w) == "baaaa");
			w = "bababab";
			assert(me.apply_word(w) == "baa");

		}

		TEST_METHOD(INTEL_TEST)
		{
			parser p;
			markov_engine me;
			string filename = "../markov_algorithm/text_systems/intel8088.txt";
			set_system_from_file(filename, me, p);

			string w = "AX";
			assert(me.apply_word(w) == "AX");
			w = "XAX";
			assert(me.apply_word(w) == "");
			w = "BXDX";
			assert(me.apply_word(w) == "");

		}

		TEST_METHOD(SORT_TEST)
		{
			parser p;
			markov_engine me;
			string filename = "../markov_algorithm/text_systems/abc_sort.txt";
			set_system_from_file(filename, me, p);

			string w = "bbca";
			assert(me.apply_word(w) == "abbc");
			w = "ccc";
			assert(me.apply_word(w) == "ccc");
			w = "aaca";
			assert(me.apply_word(w) == "aaac");

		}
	};
}
