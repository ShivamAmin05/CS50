SELECT title from movies JOIN ratings ON id = movie_id WHERE id IN(SELECT movie_id from stars WHERE person_id = (SELECT id from people WHERE name = "Chadwick Boseman")) ORDER by(rating) DESC LIMIT 5;