/**
 * @author Daniel Kos <kosdani@fit.cvut.cz>
 * @date 04.06.2023
 */

#pragma once


class CApplication {
private:



public:
    CApplication() = default;

    CApplication(const CApplication&) = delete;

    CApplication& operator =(const CApplication&) = delete;

    ~CApplication() = default;

    int Run();

};
