#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "student.hpp"
#include "student_set.hpp"

namespace {

Student S(int id) {
    std::string name = "S" + std::to_string(id);
    return Student(name.c_str(), id);
}

std::string str(const StudentSet& set) {
    std::ostringstream os;
    os << set;
    return os.str();
}

} 

TEST(StudentTest, DefaultConstructor) {
    Student s;
    EXPECT_STREQ(s.getName(), "");
    EXPECT_EQ(s.getId(), 0);
}

TEST(StudentTest, ConstructorStoresFields) {
    Student s("Anna", 7);
    EXPECT_STREQ(s.getName(), "Anna");
    EXPECT_EQ(s.getId(), 7);
}

TEST(StudentTest, NullNameBecomesEmpty) {
    Student s(nullptr, 1);
    EXPECT_STREQ(s.getName(), "");
}

TEST(StudentTest, EqualityByIdOnly) {
    EXPECT_TRUE(Student("Anna", 1) == Student("Boris", 1));
    EXPECT_FALSE(Student("Anna", 1) == Student("Anna", 2));
}

TEST(StudentTest, CopyIsDeep) {
    Student a("Anna", 1);
    Student b(a);
    EXPECT_STREQ(b.getName(), "Anna");
    EXPECT_NE(a.getName(), b.getName()); 
}

TEST(StudentTest, CopyAssignmentIsDeep) {
    Student a("Anna", 1);
    Student b("Boris", 2);
    b = a;
    EXPECT_STREQ(b.getName(), "Anna");
    EXPECT_EQ(b.getId(), 1);
    EXPECT_NE(a.getName(), b.getName());
}

TEST(StudentTest, SelfAssignment) {
    Student a("Anna", 1);
    Student& ref = a;
    a = ref;
    EXPECT_STREQ(a.getName(), "Anna");
    EXPECT_EQ(a.getId(), 1);
}

TEST(StudentTest, MoveConstructorLeavesSourceSafe) {
    Student a("Anna", 1);
    Student b(std::move(a));
    EXPECT_STREQ(b.getName(), "Anna");
    EXPECT_EQ(b.getId(), 1);
    EXPECT_STREQ(a.getName(), "");  
}

TEST(StudentTest, CopyFromMovedFromIsSafe) {
    Student a("Anna", 1);
    Student b(std::move(a));
    Student c(a);  
    Student d;
    d = a;
    EXPECT_STREQ(c.getName(), "");
    EXPECT_STREQ(d.getName(), "");
}

TEST(StudentTest, MoveAssignment) {
    Student a("Anna", 1);
    Student b("Boris", 2);
    b = std::move(a);
    EXPECT_STREQ(b.getName(), "Anna");
    EXPECT_EQ(b.getId(), 1);
}

TEST(StudentTest, SelfMoveAssignment) {
    Student a("Anna", 1);
    Student& ref = a;
    a = std::move(ref);
    EXPECT_STREQ(a.getName(), "Anna");
    EXPECT_EQ(a.getId(), 1);
}

TEST(StudentTest, Output) {
    std::ostringstream os;
    os << Student("Anna", 1);
    EXPECT_EQ(os.str(), "Name: Anna, ID: 1");
}

// ---------- StudentSet: минимальный набор из задания ----------

// 1. пустое множество
TEST(StudentSetTest, EmptySet) {
    StudentSet set;
    EXPECT_EQ(set.size(), 0u);
    EXPECT_TRUE(set.empty());
    EXPECT_FALSE(set.contains(S(1)));
    EXPECT_FALSE(set(S(1)));
}

// 2. add нового / дубликата
TEST(StudentSetTest, AddNewAndDuplicate) {
    StudentSet set;
    EXPECT_TRUE(set.add(S(1)));
    EXPECT_EQ(set.size(), 1u);
    EXPECT_FALSE(set.add(S(1)));
    EXPECT_EQ(set.size(), 1u);
    EXPECT_FALSE(set.empty());
}

TEST(StudentSetTest, DuplicateDeterminedById) {
    StudentSet set;
    EXPECT_TRUE(set.add(Student("Anna", 1)));
    EXPECT_FALSE(set.add(Student("Other", 1)));
    EXPECT_EQ(set.size(), 1u);
}

TEST(StudentSetTest, RemoveExistingAndMissing) {
    StudentSet set;
    set.add(S(1));
    set.add(S(2));
    EXPECT_TRUE(set.remove(S(1)));
    EXPECT_EQ(set.size(), 1u);
    EXPECT_FALSE(set.contains(S(1)));
    EXPECT_FALSE(set.remove(S(1)));
    EXPECT_FALSE(set.remove(S(99)));
    EXPECT_EQ(set.size(), 1u);
}

TEST(StudentSetTest, RemoveFromEmpty) {
    StudentSet set;
    EXPECT_FALSE(set.remove(S(1)));
    EXPECT_TRUE(set.empty());
}

TEST(StudentSetTest, RemovePreservesOrder) {
    StudentSet set;
    for (int i = 1; i <= 4; i++) set.add(S(i));
    set.remove(S(2));
    EXPECT_EQ(str(set), "{ Name: S1, ID: 1, Name: S3, ID: 3, Name: S4, ID: 4 }");
}

TEST(StudentSetTest, RemoveFirstAndLast) {
    StudentSet set;
    for (int i = 1; i <= 3; i++) set.add(S(i));
    EXPECT_TRUE(set.remove(S(1)));
    EXPECT_TRUE(set.remove(S(3)));
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set.contains(S(2)));
    EXPECT_TRUE(set.remove(S(2)));
    EXPECT_TRUE(set.empty());
}

TEST(StudentSetTest, AddAfterRemoveAll) {
    StudentSet set;
    set.add(S(1));
    set.remove(S(1));
    EXPECT_TRUE(set.add(S(1)));
    EXPECT_EQ(set.size(), 1u);
}

TEST(StudentSetTest, ContainsAndCallOperatorConsistent) {
    StudentSet set;
    set.add(S(1));
    set.add(S(2));
    for (int i = 0; i <= 3; i++) {
        EXPECT_EQ(set.contains(S(i)), set(S(i))) << "id=" << i;
    }
    EXPECT_TRUE(set(S(1)));
    EXPECT_FALSE(set(S(3)));
}

TEST(StudentSetTest, CallOperatorWorksOnConstSet) {
    StudentSet set;
    set.add(S(5));
    const StudentSet& cref = set;
    EXPECT_TRUE(cref(S(5)));
    EXPECT_TRUE(cref.contains(S(5)));
    EXPECT_EQ(cref.size(), 1u);
}

TEST(StudentSetTest, PlusEqualsMinusEqualsChain) {
    StudentSet set;
    set += S(1);
    (set += S(2)) += S(3);
    EXPECT_EQ(set.size(), 3u);
    (set -= S(1)) -= S(2);
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set.contains(S(3)));
    set += S(3);  // дубликат
    EXPECT_EQ(set.size(), 1u);
    set -= S(42);  // отсутствующий
    EXPECT_EQ(set.size(), 1u);
}

TEST(StudentSetTest, PlusEqualsReturnsSelf) {
    StudentSet set;
    StudentSet& r = (set += S(1));
    EXPECT_EQ(&r, &set);
    StudentSet& r2 = (set -= S(1));
    EXPECT_EQ(&r2, &set);
}

TEST(StudentSetTest, CopyConstructorIsIndependent) {
    StudentSet a;
    a.add(S(1));
    a.add(S(2));
    StudentSet b(a);
    EXPECT_EQ(b.size(), 2u);
    b.add(S(3));
    b.remove(S(1));
    EXPECT_EQ(a.size(), 2u);
    EXPECT_TRUE(a.contains(S(1)));
    EXPECT_FALSE(a.contains(S(3)));
}

TEST(StudentSetTest, CopyAssignmentIsIndependent) {
    StudentSet a;
    a.add(S(1));
    StudentSet b;
    b.add(S(10));
    b.add(S(11));
    b = a;
    EXPECT_EQ(b.size(), 1u);
    EXPECT_TRUE(b.contains(S(1)));
    EXPECT_FALSE(b.contains(S(10)));
    b.add(S(2));
    EXPECT_EQ(a.size(), 1u);
    EXPECT_FALSE(a.contains(S(2)));
}

TEST(StudentSetTest, CopyOfEmptySet) {
    StudentSet a;
    StudentSet b(a);
    EXPECT_TRUE(b.empty());
    EXPECT_TRUE(b.add(S(1)));
}

TEST(StudentSetTest, SelfAssignment) {
    StudentSet a;
    a.add(S(1));
    a.add(S(2));
    StudentSet& ref = a;
    a = ref;
    EXPECT_EQ(a.size(), 2u);
    EXPECT_TRUE(a.contains(S(1)));
    EXPECT_TRUE(a.contains(S(2)));
}

TEST(StudentSetTest, CopyAssignChain) {
    StudentSet a, b, c;
    a.add(S(1));
    c = b = a;
    EXPECT_TRUE(b == a);
    EXPECT_TRUE(c == a);
}

TEST(StudentSetTest, MoveConstructorLeavesSourceEmpty) {
    StudentSet a;
    a.add(S(1));
    a.add(S(2));
    StudentSet b(std::move(a));
    EXPECT_EQ(b.size(), 2u);
    EXPECT_TRUE(b.contains(S(2)));
    EXPECT_EQ(a.size(), 0u);
    EXPECT_TRUE(a.empty());
    EXPECT_FALSE(a.contains(S(1)));
    // источник остаётся рабочим
    EXPECT_TRUE(a.add(S(5)));
    EXPECT_EQ(a.size(), 1u);
}

TEST(StudentSetTest, MoveAssignmentLeavesSourceEmpty) {
    StudentSet a;
    a.add(S(1));
    StudentSet b;
    b.add(S(10));
    b.add(S(11));
    b = std::move(a);
    EXPECT_EQ(b.size(), 1u);
    EXPECT_TRUE(b.contains(S(1)));
    EXPECT_FALSE(b.contains(S(10)));
    EXPECT_TRUE(a.empty());
    EXPECT_TRUE(a.add(S(7)));
}

TEST(StudentSetTest, MoveFromEmpty) {
    StudentSet a;
    StudentSet b(std::move(a));
    EXPECT_TRUE(a.empty());
    EXPECT_TRUE(b.empty());
    StudentSet c;
    c.add(S(1));
    c = std::move(b);
    EXPECT_TRUE(c.empty());
}

TEST(StudentSetTest, SelfMoveAssignment) {
    StudentSet a;
    a.add(S(1));
    StudentSet& ref = a;
    a = std::move(ref);
    EXPECT_EQ(a.size(), 1u);
    EXPECT_TRUE(a.contains(S(1)));
}

TEST(StudentSetTest, MoveConstructorIsNoexcept) {
    EXPECT_TRUE(std::is_nothrow_move_constructible<StudentSet>::value);
    EXPECT_TRUE(std::is_nothrow_move_assignable<StudentSet>::value);
}

TEST(StudentSetTest, Union) {
    StudentSet a, b;
    a.add(S(1));
    a.add(S(2));
    b.add(S(2));
    b.add(S(3));
    StudentSet u = a | b;
    EXPECT_EQ(u.size(), 3u);
    for (int i = 1; i <= 3; i++) EXPECT_TRUE(u.contains(S(i)));
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 2u);
}

TEST(StudentSetTest, Intersection) {
    StudentSet a, b;
    a.add(S(1));
    a.add(S(2));
    a.add(S(3));
    b.add(S(2));
    b.add(S(3));
    b.add(S(4));
    StudentSet i = a & b;
    EXPECT_EQ(i.size(), 2u);
    EXPECT_TRUE(i.contains(S(2)));
    EXPECT_TRUE(i.contains(S(3)));
    EXPECT_FALSE(i.contains(S(1)));
    EXPECT_FALSE(i.contains(S(4)));
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.size(), 3u);
}

TEST(StudentSetTest, Difference) {
    StudentSet a, b;
    a.add(S(1));
    a.add(S(2));
    a.add(S(3));
    b.add(S(2));
    b.add(S(4));
    StudentSet d = a - b;
    EXPECT_EQ(d.size(), 2u);
    EXPECT_TRUE(d.contains(S(1)));
    EXPECT_TRUE(d.contains(S(3)));
    EXPECT_FALSE(d.contains(S(2)));
    EXPECT_FALSE(d.contains(S(4)));
    StudentSet d2 = b - a;
    EXPECT_EQ(d2.size(), 1u);
    EXPECT_TRUE(d2.contains(S(4)));
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.size(), 2u);
}

TEST(StudentSetTest, OperationsWithEmptySet) {
    StudentSet a, e;
    a.add(S(1));
    a.add(S(2));
    EXPECT_TRUE((a | e) == a);
    EXPECT_TRUE((e | a) == a);
    EXPECT_TRUE((a & e).empty());
    EXPECT_TRUE((e & a).empty());
    EXPECT_TRUE((a - e) == a);
    EXPECT_TRUE((e - a).empty());
    EXPECT_TRUE((e | e).empty());
}

TEST(StudentSetTest, OperationsWithItself) {
    StudentSet a;
    a.add(S(1));
    a.add(S(2));
    EXPECT_TRUE((a | a) == a);
    EXPECT_TRUE((a & a) == a);
    EXPECT_TRUE((a - a).empty());
}

TEST(StudentSetTest, DisjointSets) {
    StudentSet a, b;
    a.add(S(1));
    b.add(S(2));
    EXPECT_EQ((a | b).size(), 2u);
    EXPECT_TRUE((a & b).empty());
    EXPECT_TRUE((a - b) == a);
}

TEST(StudentSetTest, EqualityIgnoresOrder) {
    StudentSet a, b;
    a.add(S(1));
    a.add(S(2));
    a.add(S(3));
    b.add(S(3));
    b.add(S(1));
    b.add(S(2));
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StudentSetTest, InequalityDifferentElements) {
    StudentSet a, b;
    a.add(S(1));
    a.add(S(2));
    b.add(S(1));
    b.add(S(3));
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StudentSetTest, InequalityDifferentSize) {
    StudentSet a, b;
    a.add(S(1));
    b.add(S(1));
    b.add(S(2));
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StudentSetTest, EmptySetsEqual) {
    StudentSet a, b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StudentSetTest, EqualityIsReflexive) {
    StudentSet a;
    a.add(S(1));
    EXPECT_TRUE(a == a);
}

TEST(StudentSetTest, OutputFormat) {
    StudentSet set;
    set.add(Student("Anna", 1));
    set.add(Student("Boris", 2));
    EXPECT_EQ(str(set), "{ Name: Anna, ID: 1, Name: Boris, ID: 2 }");
}

TEST(StudentSetTest, OutputSingle) {
    StudentSet set;
    set.add(Student("Anna", 1));
    EXPECT_EQ(str(set), "{ Name: Anna, ID: 1 }");
}

TEST(StudentSetTest, OutputEmpty) {
    StudentSet set;
    EXPECT_EQ(str(set), "{  }");
}

TEST(StudentSetTest, OutputInInsertionOrder) {
    StudentSet set;
    set.add(S(3));
    set.add(S(1));
    set.add(S(2));
    EXPECT_EQ(str(set), "{ Name: S3, ID: 3, Name: S1, ID: 1, Name: S2, ID: 2 }");
}
TEST(StudentSetTest, StressThousandAdds) {
    StudentSet set;
    for (int i = 0; i < 1000; i++) {
        EXPECT_TRUE(set.add(S(i)));
    }
    EXPECT_EQ(set.size(), 1000u);
    for (int i = 0; i < 1000; i++) {
        EXPECT_FALSE(set.add(S(i)));
    }
    EXPECT_EQ(set.size(), 1000u);
    for (int i = 0; i < 1000; i++) {
        EXPECT_TRUE(set.contains(S(i)));
    }
    EXPECT_FALSE(set.contains(S(1000)));
}

TEST(StudentSetTest, StressAddRemove) {
    StudentSet set;
    for (int i = 0; i < 1000; i++) set.add(S(i));
    for (int i = 0; i < 1000; i += 2) EXPECT_TRUE(set.remove(S(i)));
    EXPECT_EQ(set.size(), 500u);
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(set.contains(S(i)), i % 2 == 1) << "id=" << i;
    }
    for (int i = 1; i < 1000; i += 2) EXPECT_TRUE(set.remove(S(i)));
    EXPECT_TRUE(set.empty());
}

TEST(StudentSetTest, StressCopyAndOperations) {
    StudentSet a, b;
    for (int i = 0; i < 1000; i++) a.add(S(i));
    for (int i = 500; i < 1500; i++) b.add(S(i));
    StudentSet copy(a);
    EXPECT_TRUE(copy == a);
    EXPECT_EQ((a | b).size(), 1500u);
    EXPECT_EQ((a & b).size(), 500u);
    EXPECT_EQ((a - b).size(), 500u);
    EXPECT_EQ((b - a).size(), 500u);
}

TEST(StudentSetTest, GrowthAcrossCapacityBoundaries) {
    StudentSet set;
    for (int i = 1; i <= 17; i++) {
        EXPECT_TRUE(set.add(S(i)));
        EXPECT_EQ(set.size(), static_cast<std::size_t>(i));
        for (int j = 1; j <= i; j++) EXPECT_TRUE(set.contains(S(j)));
    }
}

TEST(StudentSetTest, NamesSurviveReallocation) {
    StudentSet set;
    for (int i = 0; i < 20; i++) set.add(S(i));
    std::string out = str(set);
    EXPECT_NE(out.find("Name: S0, ID: 0"), std::string::npos);
    EXPECT_NE(out.find("Name: S19, ID: 19"), std::string::npos);
}