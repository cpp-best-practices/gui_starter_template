if (CMAKE_GENERATOR MATCHES "Visual Studio")

    # Read checks from the clang tidy file using PowerShell
    execute_process(COMMAND powershell "Select-String -path ${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy \"Checks:[\\s\\t]*[`\"'](.*)[`\"']\" -AllMatches  | Foreach-Object {$_.Matches} | Foreach-Object {$_.Groups[1].Value}" OUTPUT_VARIABLE ClangTidyChecks)

    # Visual Studio Code Analysis
    foreach(target IN LISTS Targets)
      set_target_properties(${target} PROPERTIES
          VS_GLOBAL_RunCodeAnalysis true

          # MSVC
          VS_GLOBAL_EnableMicrosoftCodeAnalysis true
          VS_GLOBAL_CodeAnalysisRuleSet AllRules.ruleset  # See for other rulesets: C:\Program Files (x86)\Microsoft Visual Studio\2019\Preview\Team Tools\Static Analysis Tools\Rule Sets\

          # Clang tidy
          VS_GLOBAL_EnableClangTidyCodeAnalysis true
          VS_GLOBAL_ClangTidyChecks ${ClangTidyChecks}
      )
    endforeach()
endif()
