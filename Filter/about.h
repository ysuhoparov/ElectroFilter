#ifndef ABOUT_H
#define ABOUT_H


class About
{
public:
    const char* about{ R"(
    Система управления электрофильтром работает совместно с контроллерами
полей фильтра, которые выполняют непосредственное управление источниками
питания и механизмами регенерации фильтра.

    Система ведет сбор и хранение в базе данных информации о режимах
питания фильтра, выходе из строя и замене элементов оборудования
электрофильтра.

    Система позволяет проводить управление источниками питания фильтра
(пуск - стоп) и установку параметров алгоритма регулирования напряжения
источников питания электрофильтра.  )" };

    const char* aboutFilter{ R"(
    Электрофильтр — это устройство для очистки газов от аэрозольных,
твердых или жидких частиц происходит под действием электрического поля.
В результате действия электрических сил заряженные частицы выводятся из
очищаемого газового потока и осаждаются на электродах. Зарядка частиц
происходит в поле коронного разряда.

    Электрофильтр представляет собой корпус прямолинейной или
цилиндрической формы, внутри которого смонтированы осадительные и
коронирующие электроды. Коронирующие электроды подключены к
высоковольтному источнику питания напряжением 50—60 кВ.

    Электрофильтры, в которых улавливаемые частицы
удаляются с электродов встряхиванием, называются сухими, а те,
в которых осаженные частицы смываются с электродов жидкостью или
улавливаются жидкие частицы (туман, брызги), — мокрыми.

    По числу электрических полей, через которые очищаемый газ проходит
последовательно электрофильтры разделяют на однопольные и многопольные.
Иногда электрофильтры разбивают на параллельные по ходу газа  секции.

    Очищаемый в электрофильтре газ проходит активную зону в вертикальном
или горизонтальном направлениях. По типу осадительных электродов
электрофильтры делят на пластинчатые и трубчатые. )" };

} ab;

#endif // ABOUT_H