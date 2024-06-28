#include "ui.h"
#include "assert.h"
typedef Movie Element;

void testDynamicArr() {
    Movie m1 = Movie("Blade Runner 2049", 2017, "Action/Drama", 500000, "https://www.imdb.com/title/tt1856101");
    Movie m2 = Movie("Nightcrawler", 2014, "Crime/Drama", 375000, "https://www.imdb.com/title/tt1856101");
    Movie m3 = Movie("No Country for Old Men", 2007, "Crime/Thriller", 700000, "https://www.imdb.com/title/tt1856101");
    auto* d = new DynamicArray<Movie>();
    d->addItem(m1);
    assert(d->getItem(0).getName() == "Blade Runner 2049");
    d->removeItem(0);
    assert(d->getSize() == 0);
    d->addItem(m2);
    d->addItem(m3);
    assert(d->getSize() == 2);
    assert(d->getItem(0).getYear() == 2014);
    assert(d->getItem(1).getName() == "No Country for Old Men");
    assert(d->findItem(m3) == 1);
    assert(d->findItem(m1) == -1);
    d->resize();
    assert(d->getItemPtr(0) != nullptr);
    delete d;

}

void testDomain() {
    Movie m1 = Movie("Blade Runner 2049", 2017, "Action/Drama", 500000, "https://www.imdb.com/title/tt1856101");
    Movie m2 = Movie("Nightcrawler", 2014, "Crime/Drama", 375000, "https://www.imdb.com/title/tt1856101");
    Movie m3 = Movie("No Country for Old Men", 2007, "Crime/Thriller", 700000, "https://www.imdb.com/title/tt1856101");
    assert(m1.getYear() == 2017);
    assert(m2.getName() == "Nightcrawler");
    assert(m3.getLikes() == 700000);
    m1.setName("ABC");
    assert(m1.getName() == "ABC");
    m2.setLink("123");
    assert(m2.getLink() == "123");
    m3.setGenre("genre!");
    assert(m3.getGenre() == "genre!");
    assert(m1.toString().compare("NAME: ABC, YEAR: 2017, GENRE: Action/Drama, LIKES: 500000, LINK: https://www.imdb.com/title/tt1856101\n") == 0);
    //free(&m1);
    //free(&m2);
    //free(&m3);
}

void testRepo() {
    auto* r = new Repository();
    Movie m1 = Movie("Blade Runner 2049", 2017, "Action/Drama", 500000, "https://www.imdb.com/title/tt1856101");
    Movie m2 = Movie("Nightcrawler", 2014, "Crime/Drama", 375000, "https://www.imdb.com/title/tt1856101");
    Movie m3 = Movie("No Country for Old Men", 2007, "Crime/Thriller", 700000, "https://www.imdb.com/title/tt1856101");
    r->addMovie(m1);
    assert(r->addMovie(m2));
    assert(r->getSize() == 2);
    assert(r->findMovie("Nightcrawler", 2014) == 1);
    assert(r->findMovie("no movie", 2023) == -1);
    assert(r->removeMovie("Blade Runner 2049", 2017) == 1);
    assert(r->getSize() == 1);
    assert(r->findMovie("Nightcrawler", 2014) == 0);
    assert(r->addMovie(m2) == -1);
    assert(r->getMoviePtr(0) != nullptr);
    delete r;
}

void testService() {
    auto* s = new Service();
    Movie m1 = Movie("Blade Runner 2049", 2017, "Action/Drama", 500000, "https://www.imdb.com/title/tt1856101");
    Movie m2 = Movie("Nightcrawler", 2014, "Crime/Drama", 375000, "https://www.imdb.com/title/tt1856101");
    Movie m3 = Movie("No Country for Old Men", 2007, "Crime/Thriller", 700000, "https://www.imdb.com/title/tt1856101");
    assert(s->updateGenre("Nightcrawler", 2014, "new genre!"));
    assert(s->getRepo()->getMovie(9).getGenre() == "new genre!");
    s->deleteMovieService(m1);
    assert(s->getRepo()->getMovie(0).getName() == "No Country for Old Men");
    s->updateLikes("Nightcrawler", 2014, 1000000);
    assert(s->getRepo()->getMovie(8).getLikes() == 1000000);
    s->updateLink("Nightcrawler", 2014, "new link!");
    assert(s->getRepo()->getMovie(8).getLink() == "new link!");
    s->updateName("Nightcrawler", 2014, "new name!");
    assert(s->getRepo()->getMovie(8).getName() == "new name!");
    s->updateYear("new name!", 2014, 3000);
    assert(s->getRepo()->getMovie(8).getYear() == 3000);
    delete s;
}